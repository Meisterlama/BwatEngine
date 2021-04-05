#ifndef ENGINE_ECS_SYSTEMS_AUDIO_HPP
#define ENGINE_ECS_SYSTEMS_AUDIO_HPP

#include "ECS/System.hpp"
#include "ECS/Components/AudioSourceComponent.hpp"

namespace BwatEngine
{
    class SoundSystem : public System
    {
        Math::RNG rng;
    public:
				// why are you defining these functions in .hpp instead of in .cpp ?
        void Init() {
            Audio::InitOpenAL();
            rng.ResetSeed(0);
        }

        void Update()
        {
            auto& coordinator = *Coordinator::GetInstance();

            // auto default behavior is copy
						// your range for loop copy each of your entity
						// dunno if it is relevant since I don't know the type
						for (auto entity : entities)
            {
                auto& component = coordinator.GetComponent<AudioSourceComponent>(entity);
                auto& transform = coordinator.GetComponent<TransformComponent>(entity).transform;
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
