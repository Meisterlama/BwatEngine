#ifndef ENGINE_ECS_SYSTEMS_PHYSICS_HPP
#define ENGINE_ECS_SYSTEMS_PHYSICS_HPP

#include "ECS/System.hpp"

#include "Physic/PhysicScene.hpp"

namespace BwatEngine
{
    class PhysicsSystem : public System
    {
    public:

        void Init(PhysicScene* physicScene);
        void Update();
        
    private:

        PhysicScene* ptrPhysicScene = nullptr;
    };
}

#endif //ENGINE_ECS_SYSTEMS_PHYSICS_HPP
