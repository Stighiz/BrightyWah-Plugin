/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MyTheme.h"
#include "PluginParameters.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginEditor  : public juce::AudioProcessorEditor
{
public:
    //==============================================================================
    PluginEditor (BrightyWahAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~PluginEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    BrightyWahAudioProcessor& audioProcessor;
    AudioProcessorValueTreeState& parameters;

    std::unique_ptr<ButtonAttachment> externalSidechainAttachment;
    std::unique_ptr<SliderAttachment> outputLevelAttachment;
    std::unique_ptr<SliderAttachment> rmsTimeAttachment;
    std::unique_ptr<SliderAttachment> fAttachment;
    std::unique_ptr<SliderAttachment> qAttachment;
    std::unique_ptr<SliderAttachment> amountAttachment;
    std::unique_ptr<SliderAttachment> LPFreqAttachment;
    std::unique_ptr<SliderAttachment> LPQAttachment;

    MyLookAndFeel myTheme;
    MyLookAndFeel myTheme_5_tick;

    juce::Image backgroundImage;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Slider> rmsTimeSlider;
    std::unique_ptr<juce::ToggleButton> externalSidechainButton;
    std::unique_ptr<juce::Slider> fminSlider;
    std::unique_ptr<juce::Slider> amountSlider;
    std::unique_ptr<juce::Slider> qSlider;
    std::unique_ptr<juce::Slider> LPCutoffFreqSlider;
    std::unique_ptr<juce::Slider> LPQSlider;
    std::unique_ptr<juce::Slider> outputLevelSlider;
    std::unique_ptr<juce::Drawable> drawable1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

