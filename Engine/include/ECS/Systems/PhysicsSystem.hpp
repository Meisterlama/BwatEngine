#ifndef ENGINE_ECS_SYSTEMS_PHYSICS_HPP
#define ENGINE_ECS_SYSTEMS_PHYSICS_HPP

#include "ECS/System.hpp"

// you don't need to include these files in your .hpp
// be careful of your compile time
// bad include management can severly increase your compile time
#include "ECS/Components/RigidBodyComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/GravityComponent.hpp"

#include "ECS/Components/GravityComponent.hpp"
#include "ECS/Components/RigidBodyComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"

#include "Scene.hpp"

namespace BwatEngine
{
    class PhysicsSystem : public System
    {
    public:

        void Init(Scene* scene, const Math::Vec3f &gravity);
        void Update();
        
    private:

        Scene* ptrScene = nullptr;
    };
}

#endif //ENGINE_ECS_SYSTEMS_PHYSICS_HPP
