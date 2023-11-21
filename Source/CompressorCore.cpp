/*
  ==============================================================================

    CompressorCore.cpp
    Created: 19 Nov 2023 7:40:23pm
    Author:  Mordorkonan

  ==============================================================================
*/

#include "CompressorCore.h"
//============================================================

CompressorCore::CompressorCore() noexcept { }

float CompressorCore::processSample(float sample) noexcept
//============================================================
// This function applies ratio on sample returning compressed
// value. Threshold and ratio are calculated externally.
//============================================================
{
    auto sampleDb = juce::Decibels::gainToDecibels(std::abs(sample));
    if (sampleDb > threshold) { multiplier = ratio; }
    else { multiplier = 1.0f; }
    return sample * multiplier;
}

void CompressorCore::applyAttack() { }

void CompressorCore::applyRelease() { }

float CompressorCore::getRatio() const noexcept { return ratio; }

void CompressorCore::setRatio(float newRatio) noexcept { ratio = newRatio; }

bool CompressorCore::getBypass() const noexcept { return bypass; }

void CompressorCore::setBypass(bool state) noexcept { bypass = state; }

float CompressorCore::getThreshold() const noexcept { return threshold; }

void CompressorCore::setThreshold(float th) noexcept { threshold = th; }

void CompressorCore::calculateMultiplier()
{
    if (signalOverThreshold) { multiplier = ratio; }
    else { multiplier = 1; }
}
