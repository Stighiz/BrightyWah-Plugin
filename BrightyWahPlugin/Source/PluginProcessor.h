#pragma once

#include <JuceHeader.h>
#include "PluginParameters.h"
#include "FeatureExtraction.h"
#include "WahFilter.h"

class BrightyWahAudioProcessor  : public juce::AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
    BrightyWahAudioProcessor();
    ~BrightyWahAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (const double sampleRate, const int samplesPerBlock) override;
    void releaseResources() override;
    
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override {return JucePlugin_Name;};

    bool acceptsMidi() const override {return false;};
    bool producesMidi() const override {return false;};
    bool isMidiEffect() const override {return false;};
    double getTailLengthSeconds() const override {return 0.0;};

    //==============================================================================
    int getNumPrograms() override {return 1;};
    int getCurrentProgram() override {return 0;};
    void setCurrentProgram (int index) override {};
    const juce::String getProgramName (int index) override {return {};};
    void changeProgramName (int index, const juce::String& newName) override {};

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    AudioVisualiserComponent waveViewer;

private:
    void parameterChanged(const String& paramID, float newValue) override;
    AudioProcessorValueTreeState parameters;
    
    bool externalSidechain = Parameters::DEFAULT_EXTERNAL_SIDECHAIN;
    AudioBuffer<float> auxBuffer;
    SmoothedValue<float, ValueSmoothingTypes::Linear> gain;
    TPTFilter wahFilter;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrightyWahAudioProcessor)
};
