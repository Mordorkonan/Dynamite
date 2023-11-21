/*
  ==============================================================================

    FIFO.h
    Created: 19 Nov 2023 7:21:50pm
    Author:  Mordorkonan

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

template <class Type, size_t size>
class Fifo
{
public:
    size_t getSize() noexcept { return size; }

    void prepare(int numSamples, int numChannels)
    {
        for (auto& buffer : buffers)
        {
            buffer.setSize(numChannels, numSamples, false, true, false);
            buffer.clear();
        }
    }
    int getNumAvailableForReading() const { return fifo.getNumReady(); }

    int getAvailableSpace() const { return fifo.getFreeSpace(); }

    bool pull(Type& t)
    {
        auto readIndex = fifo.read(1);
        if (readIndex.blockSize1 > 0)
        {
            t = buffers[readIndex.startIndex1];
            return true;
        }
        else { return false; }
    }
    bool push(Type& t)
    {
        auto writeIndex = fifo.write(1);
        if (writeIndex.blockSize1 > 0)
        {
            buffers[writeIndex.startIndex1] = t;
            return true;
        }
        else { return false; }
    }
private:
    juce::AbstractFifo fifo{ size };
    std::array<Type, size> buffers;
};