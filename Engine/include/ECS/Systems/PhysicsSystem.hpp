#ifndef ENGINE_ECS_SYSTEMS_PHYSICS_HPP
#define ENGINE_ECS_SYSTEMS_PHYSICS_HPP

#include "ECS/System.hpp"

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
        void BeginSimulation();
        void Update();
        void SetColliderForRigidbody(Entity entity);
        

    private:

        Scene* ptrScene = nullptr;
    };
}

#endif //ENGINE_ECS_SYSTEMS_PHYSICS_HPP