#include <ECS/Components/LightComponent.hpp>
#include "Scripting/modules.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/AudioSourceComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/RigidBodyComponent.hpp"
#include "ECS/Components/DataComponent.hpp"

namespace BwatEngine
{
    namespace AudioSourceScripting
    {
        #define AUDIOSOURCE_SETTER_GETTER(argtype, setter, getter)                                          \
            void setter(EntityID entity, argtype arg)                                                       \
            {Coordinator::GetInstance().GetComponent<AudioSourceComponent>(entity).source.setter(arg);}     \
            argtype getter(EntityID entity)                                                                 \
            {return Coordinator::GetInstance().GetComponent<AudioSourceComponent>(entity).source.getter();}

        AUDIOSOURCE_SETTER_GETTER(float, SetPitch, GetPitch);
        AUDIOSOURCE_SETTER_GETTER(float, SetGain, GetGain);
        AUDIOSOURCE_SETTER_GETTER(bool, SetLooping, GetLooping);

        void Play(EntityID entity)
        {
            Coordinator::GetInstance().GetComponent<AudioSourceComponent>(entity).source.Play();
        }

        void Stop(EntityID entity)
        {
            Coordinator::GetInstance().GetComponent<AudioSourceComponent>(entity).source.Stop();
        }

        float GetDuration(EntityID entity)
        {
            return Coordinator::GetInstance().GetComponent<AudioSourceComponent>(entity).source.GetDuration();
        }

        #undef AUDIOSOURCE_SETTER_GETTER
    }

    namespace CameraScripting
    {
        CameraComponent& GetCamera(EntityID entity)
        {
            return Coordinator::GetInstance().GetComponent<CameraComponent>(entity);
        }
    }

    namespace TransformScripting
    {
        void SetTransform(int entity, Math::Transform transform)
        {
            Coordinator::GetInstance().GetComponent<TransformComponent>(entity) = transform;
        }
        Math::Transform& GetTransform(int entity)
        {
            return Coordinator::GetInstance().GetComponent<TransformComponent>(entity);
        }
    }

    namespace RigidBodyScripting
    {
        #define RIGIDBODY_SETTER_GETTER(argtype, setter, getter)                                          \
            void setter(EntityID entity, argtype arg)                                                       \
            {Coordinator::GetInstance().GetComponent<RigidBodyComponent>(entity).setter(arg);}     \
            argtype getter(EntityID entity)                                                                 \
            {return Coordinator::GetInstance().GetComponent<RigidBodyComponent>(entity).getter();}

        RIGIDBODY_SETTER_GETTER(bool, SetStatic, GetIsStatic);
        RIGIDBODY_SETTER_GETTER(Math::Vec3f, SetVelocity, GetVelocity);
        RIGIDBODY_SETTER_GETTER(float, SetMass, GetMass);

        void AddForce(EntityID entity, Math::Vec3f force)
        {
            Coordinator::GetInstance().GetComponent<RigidBodyComponent>(entity).AddForce(force);
        }

        void LockRotation(EntityID entity, bool lockX, bool lockY, bool lockZ)
        {
            Coordinator::GetInstance().GetComponent<RigidBodyComponent>(entity).LockRotation(lockX, lockY, lockZ);
        }

        bool GetLockX(EntityID entity)
        {
            return Coordinator::GetInstance().GetComponent<RigidBodyComponent>(entity).GetXLockState();
        }

        bool GetLockY(EntityID entity)
        {
            return Coordinator::GetInstance().GetComponent<RigidBodyComponent>(entity).GetYLockState();
        }

        bool GetLockZ(EntityID entity)
        {
            return Coordinator::GetInstance().GetComponent<RigidBodyComponent>(entity).GetZLockState();
        }

        #undef RIGIDBODY_SETTER_GETTER
    }

    namespace LightScripting
    {
        LightComponent& GetLight(EntityID entity)
        {
            return Coordinator::GetInstance().GetComponent<LightComponent>(entity);
        }
    }

    namespace DataScripting
    {
        std::string GetName(EntityID entity)
        {
            Coordinator& coordinator = Coordinator::GetInstance();
            if (coordinator.HaveComponent<DataComponent>(entity))
                return coordinator.GetComponent<DataComponent>(entity).name;
            return "";
        }
    }

    sol::table open_components(sol::this_state s)
    {
        sol::state_view lua(s);

        sol::table module = lua.create_table();

        #define REGISTER_FUNC(ns, func) module.set_function(#func, ns::func)

        REGISTER_FUNC(AudioSourceScripting, SetPitch);
        REGISTER_FUNC(AudioSourceScripting, GetPitch);
        REGISTER_FUNC(AudioSourceScripting, SetGain);
        REGISTER_FUNC(AudioSourceScripting, GetGain);
        REGISTER_FUNC(AudioSourceScripting, SetLooping);
        REGISTER_FUNC(AudioSourceScripting, GetLooping);
        REGISTER_FUNC(AudioSourceScripting, Play);
        REGISTER_FUNC(AudioSourceScripting, Stop);
        REGISTER_FUNC(AudioSourceScripting, GetDuration);

        #define CAMERA_MEMBER(member) #member, &CameraComponent::member
        module.new_usertype<CameraComponent>("CameraComponent",
                                             CAMERA_MEMBER(isOrtho),
                                             CAMERA_MEMBER(near),
                                             CAMERA_MEMBER(far),
                                             CAMERA_MEMBER(left),
                                             CAMERA_MEMBER(right),
                                             CAMERA_MEMBER(top),
                                             CAMERA_MEMBER(bottom),
                                             CAMERA_MEMBER(aspect),
                                             CAMERA_MEMBER(fov)
                                             );
        #undef CAMERA_MEMBER

        REGISTER_FUNC(CameraScripting, GetCamera);

        #define LIGHT_MEMBER(member) #member, &LightComponent::member

        module.new_usertype<LightComponent>("LightComponent",
                                             LIGHT_MEMBER(position),
                                             LIGHT_MEMBER(direction),
                                             LIGHT_MEMBER(ambient),
                                             LIGHT_MEMBER(diffuse),
                                             LIGHT_MEMBER(specular),
                                             LIGHT_MEMBER(constant),
                                             LIGHT_MEMBER(linear),
                                             LIGHT_MEMBER(quadratic),
                                             LIGHT_MEMBER(cutoff),
                                             LIGHT_MEMBER(outerCutoff),
                                             LIGHT_MEMBER(typeoflight)
                                             );

        #undef LIGHT_MEMBER

        REGISTER_FUNC(LightScripting, GetLight);

        REGISTER_FUNC(TransformScripting, SetTransform);
        REGISTER_FUNC(TransformScripting, GetTransform);

        REGISTER_FUNC(RigidBodyScripting, SetStatic);
        REGISTER_FUNC(RigidBodyScripting, GetIsStatic);
        REGISTER_FUNC(RigidBodyScripting, SetVelocity);
        REGISTER_FUNC(RigidBodyScripting, GetVelocity);
        REGISTER_FUNC(RigidBodyScripting, SetMass);
        REGISTER_FUNC(RigidBodyScripting, GetMass);
        REGISTER_FUNC(RigidBodyScripting, AddForce);
        REGISTER_FUNC(RigidBodyScripting, LockRotation);
        REGISTER_FUNC(RigidBodyScripting, GetLockX);
        REGISTER_FUNC(RigidBodyScripting, GetLockY);
        REGISTER_FUNC(RigidBodyScripting, GetLockZ);

        REGISTER_FUNC(DataScripting, GetName);
        return module;
    }
}