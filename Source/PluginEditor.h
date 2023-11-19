/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CoreController.h"

//==============================================================================
/**
*/
class DynamiteAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DynamiteAudioProcessorEditor (DynamiteAudioProcessor&);
    ~DynamiteAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DynamiteAudioProcessor& audioProcessor;
    CoreController coreController;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DynamiteAudioProcessorEditor)
};
