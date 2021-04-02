#ifndef ENGINE_ECS_ENTITY_MANAGER_HPP
#define ENGINE_ECS_ENTITY_MANAGER_HPP
#include "Core.hpp"
#include "Debug/Logger.hpp"
#include <array>
#include <queue>
#include <cassert>

namespace BwatEngine
{
    class EntityManager
    {
        std::queue<EntityType> availableEntities{};
        std::array<Signature, MAX_ENTITIES> signatures{};
        int livingEntityCount{};

    public:
        EntityManager()
        {
            for (EntityType entity = 0; entity < MAX_ENTITIES; entity++)
            {
                availableEntities.push(entity);
            }
        }

        EntityType CreateEntity()
        {
            assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");
            EntityType id = availableEntities.front();
            availableEntities.pop();
            livingEntityCount++;

            return id;
        }

        void DestroyEntity(EntityType entity)
        {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            signatures[entity].reset();

            availableEntities.push(entity);
            livingEntityCount--;
        }

        void SetSignature(EntityType entity, Signature signature)
        {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            signatures[entity] = signature;
        }

        Signature GetSignature(EntityType entity)
        {
            assert(entity < MAX_ENTITIES && "Entity out of range.");
            return signatures[entity];
        }
    };
}

#endif //ENGINE_ECS_ENTITY_MANAGER_HPP