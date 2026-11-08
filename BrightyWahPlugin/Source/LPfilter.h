#pragma once
#include<JuceHeader.h>
#include "PluginParameters.h"

#define MAX_CH 2

class LPFilter
{
public:
	LPFilter(double defaultFrequency, float defaultQuality);
	~LPFilter();

	void prepareToPlay(const double sr);

	void processBlock(AudioBuffer<float>& buffer, const int numSamples);

	void setFrequency(double newValue);

	void setQuality(double newValue);

private:
    void reset();
    
	void updateCoefficients();

	int type;
	double frequency;
	float quality;
	double sampleRate = 44100.0;

	OwnedArray<dsp::IIR::Filter<float>> iirFilters;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LPFilter)
};
