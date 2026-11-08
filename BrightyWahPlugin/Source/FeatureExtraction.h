#pragma once
#include<JuceHeader.h>
#include "PluginParameters.h"

class RRMS
{
public:
    RRMS(float defaultTime, float defaultMaxTime);
    ~RRMS();

    void prepareToPlay(const double sr);

    void releaseResources();

    void processBlock(AudioBuffer<float>& buffer);

    void setRMSTime(float newValue);

private:
    double sampleRate = 44100.0;
    void reset();
    
    float sum = 0;
    AudioBuffer<float> history;
    int historyIndex = 0;
    
    float rmsTime;
    float maxTime;
	int windowSize = 1;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RRMS)
}; 


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


class CoBE
{
public:
    CoBE();
    ~CoBE();

    void prepareToPlay(const double sampleRate, const int numChannels, const int numSamples);
    
    void releaseResources();
    
    void processBlock(AudioBuffer<float>& scBuffer);
    
    void setRMSTime(float newValue);

private:
    AudioBuffer<float> deltaBuffer;
    
    void applyFilter(AudioBuffer<float>& scBuffer, AudioBuffer<float>& deltaBuffer);

    RRMS peakDetectorMainBuffer;
    RRMS peakDetectorDeltaBuffer;
    
    AudioBuffer<float> brightnessBuffer;
    
    float oldSample = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CoBE)
};


