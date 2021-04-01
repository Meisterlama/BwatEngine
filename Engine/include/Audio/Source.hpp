#ifndef ENGINE_AUDIO_SOURCE_HPP
#define ENGINE_AUDIO_SOURCE_HPP

#include "Audio/Sound.hpp"
#include "Math/Vector/Vector3.hpp"
#include "Audio/Buffer.hpp"

namespace BwatEngine::Audio
    {
        struct AudioData;
        class Source
        {
        private:
            Buffer buffer{};
            ALuint sourceID{};
            float length{};

        public:
            Source();
            Source(const AudioData& audioData);

            ~Source();

            void SetPitch(float pitch);
            void SetGain(float gain);
            void SetPosition(Math::Vec3f pos);
            void SetVelocity(Math::Vec3f vel);
            void SetLooping(bool loop);

            float GetPitch();
            float GetGain();
            bool GetLooping();

            void SetAudioData(const AudioData& audioData);

            void Play();
            void Stop();

            const ALuint& GetID() const { return sourceID; }
            const float& GetDuration() const { return length; }
        };
    }

#endif // ENGINE_AUDIO_SOURCE_HPP