/*
  ==============================================================================

    CompressorCore.h
    Created: 19 Nov 2023 7:40:23pm
    Author:  Mordorkonan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CompressorCore
{
public:
    CompressorCore() noexcept;

    void applyAttack();
    void applyRelease();

    float getRatio() const noexcept;
    void setRatio(float newRatio) noexcept;

    bool getBypass() const noexcept;
    void setBypass(bool state) noexcept;

    float getThreshold() const noexcept;
    void setThreshold(float th) noexcept;

    template <class ProcessContext>
    void process(const ProcessContext& buffer) noexcept;
    float processSample(float sample) noexcept;
    void calculateMultiplier();
private:
    float multiplier{ 1.0f };
    float ratio{ 0.25f };
    float threshold{ 0.0f }; // dB
    bool bypass{ false };
    bool signalOverThreshold{ false };
};

template <class ProcessContext>
void CompressorCore::process(const ProcessContext& context) noexcept
//============================================================
// To use this function it's required to extract AudioBlock
// instance from AudioBuffer<FloatType> and create 
// ProcessContext[non]Replacing instance with its help to
// pass it into this function.
//============================================================
{
    auto&& inBlock = context.getInputBlock();
    auto&& outBlock = context.getOutputBlock();
    jassert(inBlock.getNumChannels() == outBlock.getNumChannels());
    jassert(inBlock.getNumSamples() == outBlock.getNumSamples());

    auto length = inBlock.getNumSamples();
    auto numChannels = inBlock.getNumChannels();

    if (numChannels == 1)
    {
        auto* source = inBlock.getChannelPointer(0);
        auto* dest = outBlock.getChannelPointer(0);
        for (size_t i = 0; i < length; ++i) { dest[i] = source[i] * multiplier; }
    }
    else
    {
        // add ratio array with length from atomic ratio loadings

        for (size_t chan = 0; chan < numChannels; ++chan)
        {
            juce::FloatVectorOperations::multiply(
                outBlock.getChannelPointer(chan),
                inBlock.getChannelPointer(chan),
                multiplier,
                length);
        }

    }
}
