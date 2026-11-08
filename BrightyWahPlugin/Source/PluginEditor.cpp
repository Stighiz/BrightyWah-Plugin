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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (BrightyWahAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), audioProcessor(p), parameters(vts)
{
    //[Constructor_pre] You can add your own custom stuff here..
    addAndMakeVisible(audioProcessor.waveViewer);
    audioProcessor.waveViewer.setColours(Colour (0xffffdd00), Colour(80, 212, 242));
    //[/Constructor_pre]

    rmsTimeSlider.reset (new juce::Slider ("RMS Time"));
    addAndMakeVisible (rmsTimeSlider.get());
    rmsTimeSlider->setRange (0, 10, 0);
    rmsTimeSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    rmsTimeSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    rmsTimeSlider->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff263238));
    rmsTimeSlider->setColour (juce::Slider::thumbColourId, juce::Colour (0xff42a2c8));
    rmsTimeSlider->setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::black);
    rmsTimeSlider->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);
    rmsTimeSlider->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0xffffdd00));
    rmsTimeSlider->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x700068ff));
    rmsTimeSlider->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x82000000));

    rmsTimeSlider->setBounds (184, 136, 88, 80);

    externalSidechainButton.reset (new juce::ToggleButton ("External Sidechain"));
    addAndMakeVisible (externalSidechainButton.get());
    externalSidechainButton->setButtonText (juce::String());
    externalSidechainButton->setColour (juce::ToggleButton::textColourId, juce::Colour (0xffe4ff00));

    externalSidechainButton->setBounds (232, 56, 40, 32);

    fminSlider.reset (new juce::Slider ("Min frequency"));
    addAndMakeVisible (fminSlider.get());
    fminSlider->setRange (0, 10, 0);
    fminSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    fminSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    fminSlider->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff263238));
    fminSlider->setColour (juce::Slider::thumbColourId, juce::Colour (0xff42a2c8));
    fminSlider->setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::black);
    fminSlider->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);
    fminSlider->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0xffffdd00));
    fminSlider->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x700068ff));
    fminSlider->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x82000000));

    fminSlider->setBounds (56, 264, 88, 80);

    amountSlider.reset (new juce::Slider ("Amount"));
    addAndMakeVisible (amountSlider.get());
    amountSlider->setRange (0, 10, 0);
    amountSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    amountSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    amountSlider->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff263238));
    amountSlider->setColour (juce::Slider::thumbColourId, juce::Colour (0xff42a2c8));
    amountSlider->setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::black);
    amountSlider->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);
    amountSlider->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0xffffdd00));
    amountSlider->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x700068ff));
    amountSlider->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x82000000));

    amountSlider->setBounds (184, 256, 88, 104);

    qSlider.reset (new juce::Slider ("Q factor"));
    addAndMakeVisible (qSlider.get());
    qSlider->setRange (0, 10, 0);
    qSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    qSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    qSlider->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff263238));
    qSlider->setColour (juce::Slider::thumbColourId, juce::Colour (0xff42a2c8));
    qSlider->setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::black);
    qSlider->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);
    qSlider->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0xffffdd00));
    qSlider->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x700068ff));
    qSlider->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x82000000));

    qSlider->setBounds (304, 264, 104, 80);

    LPCutoffFreqSlider.reset (new juce::Slider ("Additional Smoothing"));
    addAndMakeVisible (LPCutoffFreqSlider.get());
    LPCutoffFreqSlider->setRange (0, 10, 0);
    LPCutoffFreqSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LPCutoffFreqSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    LPCutoffFreqSlider->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff263238));
    LPCutoffFreqSlider->setColour (juce::Slider::thumbColourId, juce::Colour (0xff42a2c8));
    LPCutoffFreqSlider->setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::black);
    LPCutoffFreqSlider->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);
    LPCutoffFreqSlider->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0xffffdd00));
    LPCutoffFreqSlider->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x700068ff));
    LPCutoffFreqSlider->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x82000000));

    LPCutoffFreqSlider->setBounds (96, 400, 96, 72);

    LPQSlider.reset (new juce::Slider ("Q factor"));
    addAndMakeVisible (LPQSlider.get());
    LPQSlider->setRange (0, 10, 0);
    LPQSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LPQSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    LPQSlider->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff263238));
    LPQSlider->setColour (juce::Slider::thumbColourId, juce::Colour (0xff42a2c8));
    LPQSlider->setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::black);
    LPQSlider->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);
    LPQSlider->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0xffffdd00));
    LPQSlider->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x700068ff));
    LPQSlider->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x82000000));

    LPQSlider->setBounds (264, 400, 88, 72);

    outputLevelSlider.reset (new juce::Slider ("Output Level"));
    addAndMakeVisible (outputLevelSlider.get());
    outputLevelSlider->setRange (0, 10, 0);
    outputLevelSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    outputLevelSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 60, 20);
    outputLevelSlider->setColour (juce::Slider::backgroundColourId, juce::Colour (0xff263238));
    outputLevelSlider->setColour (juce::Slider::thumbColourId, juce::Colour (0xff42a2c8));
    outputLevelSlider->setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::black);
    outputLevelSlider->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);
    outputLevelSlider->setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0xffffdd00));
    outputLevelSlider->setColour (juce::Slider::textBoxHighlightColourId, juce::Colour (0x700068ff));
    outputLevelSlider->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x82000000));

    outputLevelSlider->setBounds (472, 32, 160, 80);

    drawable1 = juce::Drawable::createFromImageData (BinaryData::limLogo_png, BinaryData::limLogo_pngSize);

    //[UserPreSize]
    externalSidechainAttachment.reset(new ButtonAttachment(parameters, Parameters::NAME_EXTERNAL_SIDECHAIN, *externalSidechainButton));
    outputLevelAttachment.reset(new SliderAttachment(parameters, Parameters::NAME_GAIN, *outputLevelSlider));
    rmsTimeAttachment.reset(new SliderAttachment(parameters, Parameters::NAME_RMS_TIME, *rmsTimeSlider));
    fAttachment.reset(new SliderAttachment(parameters, Parameters::NAME_F_MIN, *fminSlider));
    qAttachment.reset(new SliderAttachment(parameters, Parameters::NAME_Q, *qSlider));
    amountAttachment.reset(new SliderAttachment(parameters, Parameters::NAME_WAH_AMOUNT, *amountSlider));

    LPFreqAttachment.reset(new SliderAttachment(parameters, Parameters::NAME_ADDITIONAL_SMOOTHING, *LPCutoffFreqSlider));
    LPQAttachment.reset(new SliderAttachment(parameters, Parameters::NAME_ADDITIONAL_WIGGLES, *LPQSlider));

  //waveformWindow->connectTo(audioProcessor.gain.getCurrentValue());


    this->setLookAndFeel(&myTheme);

    myTheme_5_tick.setNumTicks(5);
    rmsTimeSlider->setLookAndFeel(&myTheme_5_tick);

    //[/UserPreSize]

    setSize (700, 500);


    //[Constructor] You can add your own custom stuff here..
    externalSidechainButton->setColour(juce::ToggleButton::tickColourId, juce::Colours::black);
    externalSidechainButton->setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::black);
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    externalSidechainAttachment = nullptr;
    outputLevelAttachment = nullptr;
    rmsTimeAttachment = nullptr;
    fAttachment = nullptr;
    qAttachment = nullptr;
    amountAttachment = nullptr;
    LPFreqAttachment = nullptr;
    LPQAttachment = nullptr;

    this->setLookAndFeel(nullptr);
    //[/Destructor_pre]

    rmsTimeSlider = nullptr;
    externalSidechainButton = nullptr;
    fminSlider = nullptr;
    amountSlider = nullptr;
    qSlider = nullptr;
    LPCutoffFreqSlider = nullptr;
    LPQSlider = nullptr;
    outputLevelSlider = nullptr;
    drawable1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::backBrightyWah2_jpeg, BinaryData::backBrightyWah2_jpegSize);
    g.drawImageWithin(backgroundImage, 0, 0, getWidth(), getHeight(), RectanglePlacement::stretchToFit);


    //[/UserPrePaint]

    g.fillAll (juce::Colour (0x5189dcff));

    {
        int x = 175, y = 110, width = 101, height = 24;
        juce::String text (TRANS("RMS time"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microgramma D", 18.00f, juce::Font::plain));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 351, y = 53, width = 114, height = 35;
        juce::String text (TRANS("Output level"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microgramma D", 18.00f, juce::Font::plain));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 47, y = 53, width = 176, height = 35;
        juce::String text (TRANS("External sidechain"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microgramma D", 18.00f, juce::Font::plain));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 176, y = 224, width = 104, height = 38;
        juce::String text (TRANS("Amount"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microgramma D", 18.00f, juce::Font::plain));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 312, y = 232, width = 88, height = 38;
        juce::String text (TRANS("Q factor"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microgramma D", 18.00f, juce::Font::plain));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 48, y = 368, width = 186, height = 40;
        juce::String text (TRANS("Additional smoothing"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microgramma D", 15.00f, juce::Font::plain));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 224, y = 368, width = 178, height = 40;
        juce::String text (TRANS("Additional wiggles"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microgramma D", 15.00f, juce::Font::plain));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 32, y = 232, width = 128, height = 38;
        juce::String text (TRANS("Min frequency"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microgramma D", 18.00f, juce::Font::plain));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 255, y = 13, width = 200, height = 30;
        juce::String text (TRANS("Brighty Wah"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Microgramma D", 33.80f, juce::Font::plain));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 431, y = 421, width = 62, height = 64;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (juce::Colours::black);
        jassert (drawable1 != nullptr);
        if (drawable1 != nullptr)
            drawable1->drawWithin (g, juce::Rectangle<int> (x, y, width, height).toFloat(),
                                   juce::RectanglePlacement::stretchToFit, 1.000f);
    }

    {
        int x = 487, y = 413, width = 195, height = 27;
        juce::String text (TRANS("Coded at Laboratorio di "));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 487, y = 429, width = 195, height = 27;
        juce::String text (TRANS("Informatica Musicale"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 503, y = 445, width = 170, height = 27;
        juce::String text (TRANS("Stighezza Valeria, Stucchi Jacopo"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 495, y = 461, width = 170, height = 27;
        juce::String text (TRANS("v. 1.0.0"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PluginEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    audioProcessor.waveViewer.setBounds(448, 184, 208, 208);
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public juce::AudioProcessorEditor" constructorParams="BrightyWahAudioProcessor&amp; p, AudioProcessorValueTreeState&amp; vts"
                 variableInitialisers="AudioProcessorEditor(&amp;p), audioProcessor(p), parameters(vts)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="700" initialHeight="500">
  <BACKGROUND backgroundColour="5189dcff">
    <TEXT pos="175 110 101 24" fill="solid: ff000000" hasStroke="0" text="RMS time"
          fontname="Microgramma D" fontsize="18.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="351 53 114 35" fill="solid: ff000000" hasStroke="0" text="Output level"
          fontname="Microgramma D" fontsize="18.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="47 53 176 35" fill="solid: ff000000" hasStroke="0" text="External sidechain"
          fontname="Microgramma D" fontsize="18.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="176 224 104 38" fill="solid: ff000000" hasStroke="0" text="Amount"
          fontname="Microgramma D" fontsize="18.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="312 232 88 38" fill="solid: ff000000" hasStroke="0" text="Q factor"
          fontname="Microgramma D" fontsize="18.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="48 368 186 40" fill="solid: ff000000" hasStroke="0" text="Additional smoothing"
          fontname="Microgramma D" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="224 368 178 40" fill="solid: ff000000" hasStroke="0" text="Additional wiggles"
          fontname="Microgramma D" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="32 232 128 38" fill="solid: ff000000" hasStroke="0" text="Min frequency"
          fontname="Microgramma D" fontsize="18.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="255 13 200 30" fill="solid: ff000000" hasStroke="0" text="Brighty Wah"
          fontname="Microgramma D" fontsize="33.8" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <IMAGE pos="431 421 62 64" resource="BinaryData::limLogo_png" opacity="1.0"
           mode="0"/>
    <TEXT pos="487 413 195 27" fill="solid: ff000000" hasStroke="0" text="Coded at Laboratorio di "
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="487 429 195 27" fill="solid: ff000000" hasStroke="0" text="Informatica Musicale"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="503 445 170 27" fill="solid: ff000000" hasStroke="0" text="Stighezza Valeria, Stucchi Jacopo"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="0"
          italic="0" justification="33"/>
    <TEXT pos="495 461 170 27" fill="solid: ff000000" hasStroke="0" text="v. 1.0.0"
          fontname="Default font" fontsize="12.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
  </BACKGROUND>
  <SLIDER name="RMS Time" id="1237b23e3ee56d16" memberName="rmsTimeSlider"
          virtualName="" explicitFocusOrder="0" pos="184 136 88 80" bkgcol="ff263238"
          thumbcol="ff42a2c8" rotarysliderfill="ff000000" textboxtext="ff000000"
          textboxbkgd="ffffdd00" textboxhighlight="700068ff" textboxoutline="82000000"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <TOGGLEBUTTON name="External Sidechain" id="a9fa2105e1bebd21" memberName="externalSidechainButton"
                virtualName="" explicitFocusOrder="0" pos="232 56 40 32" txtcol="ffe4ff00"
                buttonText="" connectedEdges="0" needsCallback="0" radioGroupId="0"
                state="0"/>
  <SLIDER name="Min frequency" id="a3699cfdd271c503" memberName="fminSlider"
          virtualName="" explicitFocusOrder="0" pos="56 264 88 80" bkgcol="ff263238"
          thumbcol="ff42a2c8" rotarysliderfill="ff000000" textboxtext="ff000000"
          textboxbkgd="ffffdd00" textboxhighlight="700068ff" textboxoutline="82000000"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Amount" id="51005d62fe8cd663" memberName="amountSlider"
          virtualName="" explicitFocusOrder="0" pos="184 256 88 104" bkgcol="ff263238"
          thumbcol="ff42a2c8" rotarysliderfill="ff000000" textboxtext="ff000000"
          textboxbkgd="ffffdd00" textboxhighlight="700068ff" textboxoutline="82000000"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Q factor" id="ccc5327e015a561f" memberName="qSlider" virtualName=""
          explicitFocusOrder="0" pos="304 264 104 80" bkgcol="ff263238"
          thumbcol="ff42a2c8" rotarysliderfill="ff000000" textboxtext="ff000000"
          textboxbkgd="ffffdd00" textboxhighlight="700068ff" textboxoutline="82000000"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Additional Smoothing" id="f4d03a3c24ee2a0f" memberName="LPCutoffFreqSlider"
          virtualName="" explicitFocusOrder="0" pos="96 400 96 72" bkgcol="ff263238"
          thumbcol="ff42a2c8" rotarysliderfill="ff000000" textboxtext="ff000000"
          textboxbkgd="ffffdd00" textboxhighlight="700068ff" textboxoutline="82000000"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Q factor" id="f1b510671f434a04" memberName="LPQSlider"
          virtualName="" explicitFocusOrder="0" pos="264 400 88 72" bkgcol="ff263238"
          thumbcol="ff42a2c8" rotarysliderfill="ff000000" textboxtext="ff000000"
          textboxbkgd="ffffdd00" textboxhighlight="700068ff" textboxoutline="82000000"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Output Level" id="523be46d32481c3f" memberName="outputLevelSlider"
          virtualName="" explicitFocusOrder="0" pos="472 32 160 80" bkgcol="ff263238"
          thumbcol="ff42a2c8" rotarysliderfill="ff000000" textboxtext="ff000000"
          textboxbkgd="ffffdd00" textboxhighlight="700068ff" textboxoutline="82000000"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

