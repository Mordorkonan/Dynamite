/*
  ==============================================================================

    CoreController.h
    Created: 19 Nov 2023 9:27:30pm
    Author:  Mordorkonan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "CompressorCore.h"

class CoreController : public juce::Component
{
public:
    CoreController(CompressorCore& _core);
    //void paint(juce::Graphics& g) override;
    void resized() override;

    juce::ToggleButton bypassButton;
    juce::Slider ratioSlider
    {
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
        juce::Slider::TextEntryBoxPosition::TextBoxBelow
    };
    juce::Slider thresholdSlider
    {
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
        juce::Slider::TextEntryBoxPosition::TextBoxBelow
    };
    CompressorCore& core;
};
