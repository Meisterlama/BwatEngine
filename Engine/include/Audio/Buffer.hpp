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
        ~Buffer(); // rule of three -> https://en.cppreference.com/w/cpp/language/rule_of_three

        void BufferAudioData(const AudioData& audioData);

        const ALuint& GetID() const { return bufferID; }
    };
}

#endif //ENGINE_AUDIO_BUFFER_HPP
