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
    CompressorCore(const float& _ratio) noexcept;
    void applyAttack();
    void applyRelease();
    float getRatio() noexcept;
    bool getBypass() const noexcept;
    void setBypass(bool state) noexcept;

    template <class ProcessContext>
    void process(const ProcessContext& buffer) noexcept;
    float processSample(float sample) noexcept;
private:
    float ratio{ 0.25f };
    bool bypass{ false };
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
        for (size_t i = 0; i < length; ++i) { dest[i] = source[i] * ratio; }
    }
    else
    {
        // add ratio array with length from atomic ratio loadings

        for (size_t chan = 0; chan < numChannels; ++chan)
        {
            juce::FloatVectorOperations::multiply(
                outBlock.getChannelPointer(chan),
                inBlock.getChannelPointer(chan),
                ratio,
                length);
        }

    }
}