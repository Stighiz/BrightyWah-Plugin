#include "LPfilter.h"

LPFilter::LPFilter(double defaultFrequency, float defaultQuality)
	: frequency(defaultFrequency), quality(defaultQuality)
{
	for (int f = 0; f < MAX_CH; ++f)
		iirFilters.add(new dsp::IIR::Filter<float>);
}

LPFilter::~LPFilter()
{
}

void LPFilter::prepareToPlay(const double sr)
{
	sampleRate = sr;
    reset();
	updateCoefficients();
}

void LPFilter::processBlock(AudioBuffer<float>& buffer, const int numSamples)
{
	dsp::AudioBlock<float> block(buffer.getArrayOfWritePointers(), buffer.getNumChannels(), numSamples);

    for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
	{
		dsp::AudioBlock<float> chBlock = block.getSingleChannelBlock(ch);
		dsp::ProcessContextReplacing<float> context(chBlock);
		iirFilters.getUnchecked(ch)->process(context);
	}
}

void LPFilter::setFrequency(double newValue)
{
	frequency = newValue;
	updateCoefficients();
}

void LPFilter::setQuality(double newValue)
{
	quality = newValue;
	updateCoefficients();
}

void LPFilter::reset()
{
	for (int f = 0; f < MAX_CH; ++f)
		iirFilters.getUnchecked(f)->reset();
}

void LPFilter::updateCoefficients()
{
	ReferenceCountedObjectPtr<dsp::IIR::Coefficients<float>> newCoefficients;

	newCoefficients = dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, frequency, quality);

	for (int f = 0; f < MAX_CH; ++f)
		iirFilters.getUnchecked(f)->coefficients = newCoefficients;
}
