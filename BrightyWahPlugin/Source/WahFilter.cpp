#include "WahFilter.h"

ModulationAdapter::ModulationAdapter(double defaultFmin, double defaultWahAmount)
: fMin(defaultFmin), modAmount(defaultWahAmount), LPfilter(Parameters::DEFAULT_ADDITIONAL_SMOOTHING, Parameters::DEFAULT_ADDITIONAL_WIGGLES)
{
}

ModulationAdapter::~ModulationAdapter()
{
}

void ModulationAdapter::prepareToPlay(const double sampleRate, const int numSamples, const int numChannels)
{
    fMin.reset(sampleRate, 0.020);
    modAmount.reset(sampleRate, 0.020);
    brightnessExtractor.prepareToPlay(sampleRate, numChannels, numSamples);
    LPfilter.prepareToPlay(sampleRate);
}

void ModulationAdapter::releaseResources()
{
    brightnessExtractor.releaseResources();
}

void ModulationAdapter::processBlock(AudioBuffer<float>& buffer, AudioBuffer<float>& scBuffer, const double sampleRate)
{
    const auto numSamples = buffer.getNumSamples();
    
    brightnessExtractor.processBlock(scBuffer);
    
    auto bufferData = scBuffer.getWritePointer(0);
    
    for (int s = 0; s < numSamples; ++s) {
        auto currentMin = fMin.getNextValue();
        auto currentAmount = modAmount.getNextValue();
        
        bufferData[s] = jmap(static_cast<double>(bufferData[s]), 0.0, 2.0, currentMin, currentMin + currentAmount);
        bufferData[s] = jlimit(0.0, sampleRate * 0.499, static_cast<double>(bufferData[s]));
    }

    LPfilter.processBlock(scBuffer, numSamples);
}

void ModulationAdapter::setFMin(double newValue)
{
    fMin.setTargetValue(newValue);
}

void ModulationAdapter::setModAmount(double newValue)
{
    modAmount.setTargetValue(newValue);
}

void ModulationAdapter::setAdditionalSmoothing(double newValue)
{
    LPfilter.setFrequency(newValue);
}

void ModulationAdapter::setAdditionalWiggles(float newValue)
{
    LPfilter.setQuality(newValue);
}

void ModulationAdapter::setRMSTime(float newValue)
{
    brightnessExtractor.setRMSTime(newValue);
}


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


TPTFilter::TPTFilter() 
    : modAdapter(Parameters::DEFAULT_F_MIN, Parameters::DEFAULT_WAH_AMOUNT)
{
    for (int f = 0; f < MAX_CH; ++f)
    {
        auto* filter = new dsp::StateVariableTPTFilter<float>();
        filter->reset();
        filter->setType(dsp::StateVariableTPTFilterType::bandpass);
        filter->setCutoffFrequency(Parameters::DEFAULT_F_MIN);
        filter->setResonance(Parameters::DEFAULT_Q);
        wahFilters.add(filter);
    }
}

TPTFilter::~TPTFilter()
{
    wahFilters.clear();
}

void TPTFilter::prepareToPlay(const double sampleRate, const int numSamples, const int numChannels)
{
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = numSamples;
    spec.numChannels = numChannels;
    
    for (auto* filter : wahFilters)
    {
        filter->prepare(spec);
    }
    modAdapter.prepareToPlay(sampleRate, numSamples, numChannels);

}

void TPTFilter::releaseResources()
{
    modAdapter.releaseResources();
}

void TPTFilter::processBlock(AudioBuffer<float>& buffer, AudioBuffer<float>& scBuffer, const double sampleRate)
{
    const auto numSamples = buffer.getNumSamples();
    const auto numChannels = buffer.getNumChannels();
    
    modAdapter.processBlock(buffer, scBuffer, sampleRate);
    
    auto brightnessBufferData = scBuffer.getReadPointer(0);

    for (int ch = 0; ch < numChannels; ++ch)
    {
        auto bufferData = buffer.getWritePointer(ch);
        auto* filter = wahFilters.getUnchecked(ch);

        for (int s = 0; s < numSamples; ++s)
        {
            if (!std::isnan(brightnessBufferData[s]))
            {
                float targetCutoff = brightnessBufferData[s];
                float currentCutoff = filter->getCutoffFrequency();
                float cutoffRate = 0.8f;

                if (std::abs(targetCutoff - currentCutoff) > cutoffRate)
                {
                    if (targetCutoff > currentCutoff)
                        targetCutoff = currentCutoff + cutoffRate;
                    else
                        targetCutoff = currentCutoff - cutoffRate;
                }
                filter->setCutoffFrequency(targetCutoff);
                bufferData[s] = filter->processSample(ch, bufferData[s]);
            }
        }
    }
}

void TPTFilter::setQFactor(float newValue)
{
    for (auto* filter : wahFilters)
        filter->setResonance(newValue);
}

void TPTFilter::setFMin(double newValue)
{
    modAdapter.setFMin(newValue);
}

void TPTFilter::setModAmount(double newValue)
{
    modAdapter.setModAmount(newValue);
}

void TPTFilter::setAdditionalSmoothing(double newValue)
{
    modAdapter.setAdditionalSmoothing(newValue);
}

void TPTFilter::setAdditionalWiggles(float newValue)
{
    modAdapter.setAdditionalWiggles(newValue);
}

void TPTFilter::setRMSTime(float newValue)
{
    modAdapter.setRMSTime(newValue);
}

void TPTFilter::reset()
{
    for (auto* filter : wahFilters)
    {
        filter->reset();
    }
}
