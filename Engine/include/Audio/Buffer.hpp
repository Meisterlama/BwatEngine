#ifndef ENGINE_AUDIO_BUFFER_HPP
#define ENGINE_AUDIO_BUFFER_HPP

#include "Audio/Sound.hpp"

namespace BwatEngine::Audio
{
    class Buffer
    {
        ALuint bufferID;

    public:
        Buffer();
        ~Buffer();

        void BufferAudioData(AudioData& audioData);

        const ALuint& GetID() const { return bufferID; }
    };
}

#endif //ENGINE_AUDIO_BUFFER_HPP
