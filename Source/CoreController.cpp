/*
  ==============================================================================

    CoreController.cpp
    Created: 19 Nov 2023 9:27:30pm
    Author:  Mordorkonan

  ==============================================================================
*/

#include "CoreController.h"
//============================================================

CoreController::CoreController(CompressorCore& _core) : core(_core)
{
    typedef juce::MathConstants<float> math;
    juce::NormalisableRange<double> sliderRange;
    juce::Slider::RotaryParameters rotaryParams;
    rotaryParams.startAngleRadians = math::twoPi - 0.75f * math::pi;
    rotaryParams.endAngleRadians = math::twoPi + 0.75f * math::pi;
    rotaryParams.stopAtEnd = true;

    // ratio settings
    ratioSlider.setRotaryParameters(rotaryParams);
    sliderRange.start = 1.0;
    sliderRange.end = 20.0;
    ratioSlider.setNormalisableRange(sliderRange);
    ratioSlider.onValueChange = [this]()
    {
        core.setRatio(1.0f / static_cast<float>(ratioSlider.getValue()));
    };

    // threshold settings
    thresholdSlider.setRotaryParameters(rotaryParams);
    sliderRange.start = -72.0;
    sliderRange.end = 0.0;
    thresholdSlider.setNormalisableRange(sliderRange);
    thresholdSlider.onValueChange = [this]()
    {
        core.setThreshold(static_cast<float>(thresholdSlider.getValue()));
    };

    // bypass settings
    bypassButton.onStateChange = [this]()
    {
        core.setBypass(bypassButton.getToggleState());
    };

    // visibility
    addAndMakeVisible(ratioSlider);
    addAndMakeVisible(thresholdSlider);
    addAndMakeVisible(bypassButton);
}

void CoreController::resized()
{
    auto bounds{ getLocalBounds() };
    auto fixedBounds{ bounds };
    ratioSlider.setBounds(bounds.removeFromLeft(fixedBounds.proportionOfWidth(0.3f)));
    thresholdSlider.setBounds(bounds.removeFromLeft(fixedBounds.proportionOfWidth(0.3f)));
    bypassButton.setBounds(bounds);
}
