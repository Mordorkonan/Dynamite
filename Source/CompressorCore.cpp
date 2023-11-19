/*
  ==============================================================================

    CompressorCore.cpp
    Created: 19 Nov 2023 7:40:23pm
    Author:  Mordorkonan

  ==============================================================================
*/

#include "CompressorCore.h"
//============================================================

CompressorCore::CompressorCore(const float& _ratio) noexcept : ratio(_ratio) { }

float CompressorCore::processSample(float sample) noexcept
//============================================================
// This function applies ratio on sample returning compressed
// value. Threshold and ratio are calculated externally.
//============================================================
{
    return sample * ratio;
}

void CompressorCore::applyAttack() { }

void CompressorCore::applyRelease() { }

float CompressorCore::getRatio() noexcept { return 1; }

void CompressorCore::calculateRatio()
{
    if (signalOverThreshold) { multiplier = ratio; }
    else { multiplier = 1; }
}

bool CompressorCore::getBypass() const noexcept { return bypass; }

void CompressorCore::setBypass(bool state) noexcept { bypass = state; }

float CompressorCore::getThreshold() const noexcept { return threshold; }

void CompressorCore::setThreshold(float th) noexcept { threshold = th; }
