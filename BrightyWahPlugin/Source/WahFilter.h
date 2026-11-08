#pragma once

#include <JuceHeader.h>
#include "PluginParameters.h"
#include "FeatureExtraction.h"
#include "LPfilter.h"

#define MAX_CH 2

class ModulationAdapter
{
    
public:
    ModulationAdapter(double defaultFmin, double defaultWahAmount);
    ~ModulationAdapter();
    
    void prepareToPlay(const double sampleRate, const int numSamples, const int numChannels);
    
    void processBlock(AudioBuffer<float>& buffer, AudioBuffer<float>& scBuffer, const double sampleRate);
    
    void releaseResources();
    
    void setFMin(double newValue);
    
    void setModAmount(double newValue);
    
    void setAdditionalSmoothing(double newValue);
    
    void setAdditionalWiggles(float newValue);
    
    void setRMSTime(float newValue);
    
private:
    SmoothedValue<double, ValueSmoothingTypes::Linear> fMin;
    SmoothedValue<double, ValueSmoothingTypes::Linear> modAmount;
    
    CoBE brightnessExtractor;
    LPFilter LPfilter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModulationAdapter);
};


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


class TPTFilter
{
    
public:
    TPTFilter();
    ~TPTFilter();
    
    void prepareToPlay(const double sampleRate, const int numSamples, const int numChannels);
    
    void releaseResources();
    
    void processBlock(AudioBuffer<float>& buffer, AudioBuffer<float>& scBuffer, const double sampleRate);
    
    void setQFactor(float newValue);
    
    void setFMin(double newValue);
    
    void setModAmount(double newValue);
    
    void setAdditionalSmoothing(double newValue);

    void setAdditionalWiggles(float newValue);

    void setRMSTime(float newValue);
    
private:
    void reset();
    
    ModulationAdapter modAdapter;
    //LPFilter LPfilter;
    OwnedArray<dsp::StateVariableTPTFilter<float>> wahFilters;
    
    dsp::ProcessSpec spec;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TPTFilter);
};
