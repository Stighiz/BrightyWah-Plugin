#pragma once
#include <JuceHeader.h>

namespace Parameters
{
    static const String NAME_EXTERNAL_SIDECHAIN = "EXTERNAL_SIDECHAIN";
    static const String NAME_GAIN = "GAIN";
    static const String NAME_RMS_TIME = "RMS TIME";
    static const String NAME_F_MIN = "F_MIN";
    static const String NAME_WAH_AMOUNT = "WAH_AMOUNT";
    static const String NAME_Q = "Q";
    static const String NAME_ADDITIONAL_SMOOTHING = "ADDITIONAL_SMOOTHING";
    static const String NAME_ADDITIONAL_WIGGLES = "ADDITIONAL_WIGGLES";

    static const bool DEFAULT_EXTERNAL_SIDECHAIN = false;
    static const float DEFAULT_GAIN = 0.0f;
    static const float DEFAULT_RMS_TIME = 0.010f;
    static const float MAX_RMS_TIME = 0.50f;
    static const float DEFAULT_F_MIN = 180.0;
    static const float DEFAULT_WAH_AMOUNT = 12000.0f;
    static const float DEFAULT_Q = 1.5f;
    static const float DEFAULT_ADDITIONAL_SMOOTHING = 1000.0f;
    static const float DEFAULT_ADDITIONAL_WIGGLES = 1.5f;

    static AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        std::vector<std::unique_ptr<RangedAudioParameter>> params;
        
        params.push_back(std::make_unique<AudioParameterBool>(NAME_EXTERNAL_SIDECHAIN, "External sidechain", DEFAULT_EXTERNAL_SIDECHAIN));
        params.push_back(std::make_unique<AudioParameterFloat>(NAME_GAIN, "Output level", -40.0f, 6.0f, DEFAULT_GAIN));
        params.push_back(std::make_unique<AudioParameterFloat>(NAME_RMS_TIME, "Rms time", NormalisableRange<float>(0.010f, MAX_RMS_TIME, 0.001f), DEFAULT_RMS_TIME));
        params.push_back(std::make_unique<AudioParameterFloat>(NAME_F_MIN, "Frequenza minima Wah", NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.25f), DEFAULT_F_MIN));
        params.push_back(std::make_unique<AudioParameterFloat>(NAME_WAH_AMOUNT, "Wah amount", NormalisableRange<float>(0.0f, 20000.0f, 1.0f, 0.5f), DEFAULT_WAH_AMOUNT));
        params.push_back(std::make_unique<AudioParameterFloat>(NAME_Q, "Q", NormalisableRange<float>(0.5f, 30.0f, 0.01f, 0.25f), DEFAULT_Q));
        params.push_back(std::make_unique<AudioParameterFloat>(NAME_ADDITIONAL_SMOOTHING, "Additional smoothing", NormalisableRange<float>(5.0f, 1000.0f, 1.0f, 0.25f), DEFAULT_ADDITIONAL_SMOOTHING));
        params.push_back(std::make_unique<AudioParameterFloat>(NAME_ADDITIONAL_WIGGLES, "Additional wiggles", NormalisableRange<float>(0.5f, 30.0f, 0.01f, 0.25f), DEFAULT_ADDITIONAL_WIGGLES));

        return {params.begin(), params.end()};
    }

    static void addListenerToAllParameters(AudioProcessorValueTreeState& valueTreeState, AudioProcessorValueTreeState::Listener* listener)
    {
        std::unique_ptr<XmlElement> xml(valueTreeState.copyState().createXml());
        for (auto element : xml->getChildWithTagNameIterator("PARAM"))
        {
            const String& id = element->getStringAttribute("id");
            valueTreeState.addParameterListener(id, listener);
        }
    }

}
