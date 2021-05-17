#ifndef ENGINE_ECS_SYSTEMS_PHYSICS_HPP
#define ENGINE_ECS_SYSTEMS_PHYSICS_HPP

#include "ECS/System.hpp"

namespace BwatEngine
{
    class PhysicScene;

    class PhysicsSystem : public System
    {
    public:

        PhysicsSystem(PhysicScene* physicScene) : ptrPhysicScene(physicScene) {};
        virtual void Update() override;
        
    private:

        PhysicScene* ptrPhysicScene = nullptr;
    };
}

#endif //ENGINE_ECS_SYSTEMS_PHYSICS_HPP
