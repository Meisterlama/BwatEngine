#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Core.hpp"
#include "ECS/Coordinator.hpp"

namespace BwatEngine
{
    class Entity
    {
        EntityType id{};
        static Coordinator* coordinator;
    public:
        std::string name{};

        Entity()
        {
            if (coordinator == nullptr)
            {
                InitCoordinator();
            }
            id = coordinator->CreateEntity();
        }

        Entity(EntityType _id)
        {
            id = _id;
        }

        ~Entity()
        {
//            coordinator->DestroyEntity(id);
        }

        static void InitCoordinator()
        {
            if (coordinator == nullptr)
            {
                coordinator = new Coordinator;
                coordinator->Init();
            }
        }

        static Coordinator& GetCoordinator()
        {
            if (coordinator == nullptr)
            {
                InitCoordinator();
            }
            return *coordinator;
        }

        const EntityType GetID() const
        {
            return id;
        }

        template<typename T>
        void AddComponent(T component = {})
        {
            coordinator->AddComponent<T>(id, component);
        }

        template<typename T>
        void RemoveComponent(T component = {})
        {
            coordinator->RemoveComponent<T>(id);
        }

        template<typename T>
        T& GetComponent()
        {
            return coordinator->GetComponent<T>(id);
        }

        template<typename T>
        static ComponentType GetComponentType()
        {
            if (coordinator == nullptr)
                InitCoordinator();
            return coordinator->GetComponentType<T>();
        }
    };
#ifdef ENTITY_IMPLEMENTATION
    Coordinator* Entity::coordinator = nullptr;
#endif
}

#endif // !ENTITY_HPP
