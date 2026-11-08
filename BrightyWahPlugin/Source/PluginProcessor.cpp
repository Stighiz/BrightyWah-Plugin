#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BrightyWahAudioProcessor::BrightyWahAudioProcessor()
    : AudioProcessor (BusesProperties()
                      .withInput("Input", juce::AudioChannelSet::mono(), true)
                      .withOutput("Output", juce::AudioChannelSet::mono(), true)
                      .withInput("SideChain", juce::AudioChannelSet::mono(), true)
                      )
    ,waveViewer(1)
    , parameters(*this, nullptr, "BrightyWah_parameters", Parameters::createParameterLayout())
{
    Parameters::addListenerToAllParameters(parameters, this);
    
    waveViewer.setRepaintRate(30);
    waveViewer.setBufferSize(256);
    //waveViewer.setColours(Colours::black, Colours::white);
    
    gain.setCurrentAndTargetValue(1.0f);
}

BrightyWahAudioProcessor::~BrightyWahAudioProcessor()
{
}

//==============================================================================
void BrightyWahAudioProcessor::prepareToPlay (const double sampleRate, const int samplesPerBlock)
{
    const auto numChannels = getTotalNumOutputChannels();
    
    wahFilter.prepareToPlay(sampleRate, samplesPerBlock, numChannels);
    auxBuffer.setSize(1, samplesPerBlock);
    auxBuffer.clear();
    gain.reset(sampleRate, 0.020f);
}

void BrightyWahAudioProcessor::releaseResources()
{
    auxBuffer.setSize(0, 0);
    wahFilter.releaseResources();
}

bool BrightyWahAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    if (layouts.inputBuses[1] != juce::AudioChannelSet::mono()
        && layouts.inputBuses[1] != juce::AudioChannelSet::stereo()
        && layouts.inputBuses[1] != juce::AudioChannelSet::disabled())
        return false;

    return true;
}



void BrightyWahAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    const auto sampleRate = getSampleRate();
    const auto numSamples = buffer.getNumSamples();
    const auto totalNumInputChannels = getTotalNumInputChannels();
    const auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    auto mainBuffer = getBusBuffer(buffer, true, 0);
    auto scBuffer = getBusBuffer(buffer, true, 1);

    auxBuffer.clear();
    
    AudioBuffer<float>& scSource = (externalSidechain && scBuffer.getNumSamples()) ? scBuffer : mainBuffer;
    const int numScChannels = scSource.getNumChannels();
    
    for (int ch = 0; ch < numScChannels; ++ch)
        auxBuffer.addFrom(0, 0, scSource, ch, 0, numSamples, 1.0f / numScChannels);
    
    wahFilter.processBlock(mainBuffer, auxBuffer, sampleRate);
    
    gain.applyGain(mainBuffer, numSamples);
    
    waveViewer.pushBuffer(mainBuffer);
}

//==============================================================================
bool BrightyWahAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* BrightyWahAudioProcessor::createEditor()
{
    return new PluginEditor(*this, parameters);
}

//==============================================================================
void BrightyWahAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void BrightyWahAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(parameters.state.getType()))
        {
            parameters.replaceState(ValueTree::fromXml(*xmlState));
        }
    }
}

void BrightyWahAudioProcessor::parameterChanged(const String& paramID, float newValue)
{
    if (paramID == Parameters::NAME_EXTERNAL_SIDECHAIN)
        externalSidechain = newValue > 0.5f;

    if (paramID == Parameters::NAME_GAIN)
        gain.setTargetValue(Decibels::decibelsToGain(newValue));
    
    if (paramID == Parameters::NAME_RMS_TIME)
        wahFilter.setRMSTime(newValue);
    
    if (paramID == Parameters::NAME_F_MIN)
        wahFilter.setFMin(newValue);
    
    if (paramID == Parameters::NAME_WAH_AMOUNT)
        wahFilter.setModAmount(newValue);
    
    if (paramID == Parameters::NAME_Q)
        wahFilter.setQFactor(newValue);
    
    if (paramID == Parameters::NAME_ADDITIONAL_SMOOTHING)
        wahFilter.setAdditionalSmoothing(newValue);

    if (paramID == Parameters::NAME_ADDITIONAL_WIGGLES)
        wahFilter.setAdditionalWiggles(newValue);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BrightyWahAudioProcessor();
}
