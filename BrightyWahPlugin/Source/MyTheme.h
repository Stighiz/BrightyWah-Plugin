#pragma once
#include <JuceHeader.h>

#define BORDER_WITH 3.0f
#define SCALE_TO_KNOB_RATIO 0.75f


class MyLookAndFeel : public LookAndFeel_V4 {

public:
    MyLookAndFeel();
    ~MyLookAndFeel();
    
    void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float SliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;
    
    void setNumTicks(int newValue);
    
private:
    int numTicks = 21;
};
