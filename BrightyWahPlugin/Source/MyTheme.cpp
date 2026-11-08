#include "MyTheme.h"

MyLookAndFeel::MyLookAndFeel()
{
    setColour(Slider::thumbColourId, Colours::red);
}

MyLookAndFeel::~MyLookAndFeel()
{
}

void MyLookAndFeel::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float SliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider)
{
    // Useful variables
    const float radius = jmin(width, height) * 0.5f * SCALE_TO_KNOB_RATIO - BORDER_WITH * 0.5f;
    const auto centreX = x + width * 0.5f;
    const auto centreY = y + height * 0.5f;
    const auto rx = centreX - radius;
    const auto ry = centreY - radius;
    const auto rw = radius * 2.0f;
    
    //const Colour brightColour = Colour(Colours::aqua);
    //const Colour darkColour = Colour(Colours::blue);
    const Colour darkColour = Colour(0, 143, 211);
    const Colour brightColour = Colour(80, 212, 242);
    
    // Draw knob
    //g.setColour(Colours::darkblue);
    g.setGradientFill(ColourGradient(darkColour, rx, ry, brightColour.brighter(0.2), rx, ry + rw, false));
    g.fillEllipse(rx, ry, rw, rw);
    
    // Draw outline
    //g.setColour(Colours::lightblue);
    g.setGradientFill(ColourGradient(brightColour.brighter(0.9), rx, ry, darkColour.darker(0.6), rx, ry + rw, false));
    //g.setGradientFill(ColourGradient(Colours::aqua, rx, ry, Colours::aqua.darker(0.3), rx, ry + rw, false));
    g.drawEllipse(rx, ry, rw, rw, BORDER_WITH);
    
    // Prepare pointer shape
    Path p;
    const auto pointerLength = radius * 0.4f;
    const auto pointerThickness = 2.0f;
    p.addRectangle( - (pointerThickness * 0.5f), - radius + BORDER_WITH, pointerThickness, pointerLength);
    
    // Draw pointer shape
    //const auto angle = rotaryStartAngle + SliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    const auto angle = jmap(SliderPosProportional, rotaryStartAngle, rotaryEndAngle);
    p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));
    g.setColour(Colours::black);
    g.fillPath(p);
    
    // Draw ticks
    Path originaleShape, t;
    auto tickThickness = 2.5f;
    originaleShape.addEllipse( - (tickThickness * 0.5f), - (radius / SCALE_TO_KNOB_RATIO), tickThickness, tickThickness);
    g.setColour(Colours::black);
    
    for (int i = 0; i < numTicks; ++i)
    {
        t = originaleShape;
        auto normalizedValue = pow((float) i / (numTicks - 1), (float)slider.getSkewFactor());
        float angle = jmap(normalizedValue, rotaryStartAngle, rotaryEndAngle);
        t.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));
        g.fillPath(t);
    }
    
}

void MyLookAndFeel::setNumTicks(int newValue)
{
    numTicks = newValue;
}
