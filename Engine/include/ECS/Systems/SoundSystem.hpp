#ifndef ENGINE_ECS_SYSTEMS_AUDIO_HPP
#define ENGINE_ECS_SYSTEMS_AUDIO_HPP

#include "ECS/System.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/AudioSourceComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/ListenerComponent.hpp"

namespace BwatEngine
{
    class SoundSystem : public System
    {
        Signature listenerSignature;
    public:
        SoundSystem() {
            Audio::InitOpenAL();
            listenerSignature.set(Coordinator::GetInstance().GetComponentType<ListenerComponent>());
            listenerSignature.set(Coordinator::GetInstance().GetComponentType<TransformComponent>());
        }

        virtual void Update() override
        {
            auto& coordinator = Coordinator::GetInstance();
            for (auto entity : entities)
            {
                auto& component = coordinator.GetComponent<AudioSourceComponent>(entity);
                auto& transform = coordinator.GetComponent<TransformComponent>(entity);
                component.source.SetPosition(transform.position);
            }

            for (auto entity : coordinator.GetEntitiesWithSignature(listenerSignature))
            {
                auto& transform = coordinator.GetComponent<TransformComponent>(entity);

                Math::Vec3f forwardVec = transform.rotation.Rotate({0, 0, 1}).Normalize();
                Math::Vec3f upVec = transform.rotation.Rotate({0, 1,0}).Normalize();

                float orientation[6] = {
                    forwardVec.X,
                    forwardVec.Y,
                    forwardVec.Z,
                    upVec.X,
                    upVec.Y,
                    upVec.Z,
                };
                alListenerfv(AL_POSITION, transform.position.values);
                alListenerfv(AL_ORIENTATION, orientation);
            }
        }

        ~SoundSystem()
        {
            Audio::ShutdownOpenAL();
        }
    };
}
#endif //ENGINE_ECS_SYSTEMS_AUDIO_HPP
