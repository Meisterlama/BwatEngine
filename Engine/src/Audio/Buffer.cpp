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
//        alDeleteBuffers(1, &bufferID);
//        CheckALErrors();
    }

    void Audio::Buffer::BufferAudioData(const AudioData &audioData)
    {
        alBufferData(bufferID, AL_FORMAT_MONO16, audioData.samples.data(), audioData.samples.size(), audioData.sampleRate * 2);
    }
}