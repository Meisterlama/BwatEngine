#ifndef ENGINE_ECS_SYSTEMS_AUDIO_HPP
#define ENGINE_ECS_SYSTEMS_AUDIO_HPP

#include "ECS/System.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/AudioSourceComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"

namespace BwatEngine
{
    class SoundSystem : public System
    {
        Math::RNG rng;
    public:
        SoundSystem() {
            Audio::InitOpenAL();
            rng.ResetSeed(0);
        }

        virtual void Update() override
        {
            auto& coordinator = Coordinator::GetInstance();
            for (auto entity : entities)
            {
                auto& component = coordinator.GetComponent<AudioSourceComponent>(entity);
                auto& transform = coordinator.GetComponent<TransformComponent>(entity);
                ALint state;
                alGetSourcei(component.source.GetID(), AL_SOURCE_STATE, &state);
                component.source.SetPosition(transform.position);

                if (state != AL_PLAYING)
                {
                    component.source.SetGain(1);
                    component.source.SetPitch(rng.RollRandomFloatInRange(0.5, 2));
                    component.source.Play();
                }
            }
        }

        ~SoundSystem()
        {
            Audio::ShutdownOpenAL();
        }
    };
}
#endif //ENGINE_ECS_SYSTEMS_AUDIO_HPP
