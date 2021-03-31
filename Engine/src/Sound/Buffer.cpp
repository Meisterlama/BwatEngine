#include "Audio/Buffer.hpp"

namespace BwatEngine::Audio
{
    Audio::Buffer::Buffer()
    {
        alGenBuffers(1, &bufferID);
        CheckALErrors();
    }

    Audio::Buffer::~Buffer()
    {
        alDeleteBuffers(1, &bufferID);
        CheckALErrors();
    }

    void Audio::Buffer::BufferAudioData(AudioData &audioData)
    {
        alBufferData(bufferID, audioData.format, audioData.samples.data(), audioData.samples.size(), audioData.sampleRate);
    }
}