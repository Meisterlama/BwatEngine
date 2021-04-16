#ifndef ENGINE_ECS_ENTITY_MANAGER_HPP
#define ENGINE_ECS_ENTITY_MANAGER_HPP
#include <vector>
#include <queue>
#include "Debug/Logger.hpp"

namespace BwatEngine
{
    class EntityManager
    {
        std::queue<EntityID> availableEntities{};
        EntityID nextEntity = 1;
        // TODO: Manage vector reallocation to handle more entities than default MAX_ENTITIES
        std::vector<Signature> signatures{};
        int livingEntityCount{};

    public:
        EntityManager()
        {
            signatures.resize(MAX_ENTITIES);
        }

        EntityID CreateEntity()
        {
            if (livingEntityCount > MAX_ENTITIES)
            {
                LogError("Too many entities in existence.");
                return 0;
            }
            EntityID id = nextEntity;
            if (!availableEntities.empty())
            {
                id = availableEntities.front();
                availableEntities.pop();
            }
            else
            {
                nextEntity++;
            }
            livingEntityCount++;

            return id;
        }

        void DestroyEntity(EntityID entity)
        {
            if(entity > MAX_ENTITIES)
            {
                LogError("EntityID out of range.");
                return;
            }

            signatures[entity].reset();

            availableEntities.push(entity);
            livingEntityCount--;
        }

        void SetSignature(EntityID entity, Signature signature)
        {
            if(entity > MAX_ENTITIES)
            {
                LogError("EntityID out of range.");
                return;
            }

            signatures[entity] = signature;
        }

        Signature GetSignature(EntityID entity)
        {
            if(entity > MAX_ENTITIES)
            {
                LogError("EntityID out of range.");
                return 0;
            }
            return signatures[entity];
        }
    };
}

#endif //ENGINE_ECS_ENTITY_MANAGER_HPP