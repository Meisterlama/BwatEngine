#include <string>
#include "ECS/Coordinator.hpp"
#include "ECS/Components/DataComponent.hpp"


namespace BwatEngine
{
    Coordinator& Coordinator::GetInstance()
    {
         static Coordinator coordinator;
         return coordinator;
    }

    void Coordinator::ClearInstance()
    {
        DestroyAllEntities();
        systemManager.DestroySystems();
        LogDebug("[ECS] Coordinator was cleared");
    }

    EntityID Coordinator::CreateEntity()
    {
            auto entity = entityManager.CreateEntity();
            entities.push_back(entity);
            sceneMap[entity].id = entity;

            return entity;
    }

    bool Coordinator::IsValid(EntityID entity)
    {
        return entityManager.IsValid(entity);
    }

    void Coordinator::DestroyEntity(EntityID entity)
    {
        entityManager.DestroyEntity(entity);

        componentManager.EntityDestroyed(entity);

        systemManager.EntityDestroyed(entity);

        for (int i = 0; i < entities.size(); i++)
        {
            if (entities[i] == entity)
            {
                entities[i] = entities.back();
                entities.pop_back();
            }
        }

        for (auto& node : sceneMap[entity].children)
        {
            node->parent = nullptr;
        }
        sceneMap.erase(entity);

    }

    void Coordinator::DestroyAllEntities()
    {
        LogInfo("[ECS] Destroying all entities...");
        for (size_t size = entities.size(); size != 0; size--)
        {
            DestroyEntity(entities[0]);
        }
    }


    std::vector<EntityID> Coordinator::GetEntitiesList() const
    {
        return entities;
    }

    std::vector<EntityID> Coordinator::GetEntitiesWithSignature(Signature signature)
    {
        std::vector<EntityID> retEntities;
        for (auto entity : entities)
        {
            auto entitySignature = GetEntitySignature(entity);
            if ((entitySignature & signature) == signature)
                retEntities.push_back(entity);
        }

        return retEntities;
    }

    EntityID Coordinator::GetEntityWithName(const std::string& name)
    {
        Signature signature;
        signature.set(GetComponentType<DataComponent>());
        for (EntityID entity : GetEntitiesWithSignature(signature))
        {
            std::string entityName = GetComponent<DataComponent>(entity).name;
            if (entityName == name)
            {
                return entity;
            }
        }
        return 0;
    }

    Signature Coordinator::GetEntitySignature(EntityID entity) const
    {
        return entityManager.GetSignature(entity);
    }

    void Coordinator::SetParent(EntityID entity, EntityID parent)
    {
        if (parent == 0)
        {
            sceneMap[entity].parent = nullptr;
            return;
        }
        sceneMap[entity].parent = &sceneMap[parent];
        sceneMap[parent].children.push_back(&sceneMap[entity]);
    }

    SceneNode& Coordinator::GetNode(EntityID entity)
    {
        return sceneMap[entity];
    }

    std::vector<EntityID> Coordinator::GetRootEntities() const
    {
        std::vector<EntityID> rootEntities;
        for (auto& [id, node] : sceneMap)
        {
            if (node.parent == nullptr)
            {
                rootEntities.push_back(id);
            }
        }
        return rootEntities;
    }
}