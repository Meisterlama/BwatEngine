#include "ECS/Coordinator.hpp"

namespace BwatEngine
{
    Coordinator& Coordinator::GetInstance()
    {
         static Coordinator coordinator;
         return coordinator;
    }

    EntityID Coordinator::CreateEntity()
    {
            auto entity = entityManager.CreateEntity();
            entities.push_back(entity);
            sceneMap[entity].id = entity;
            return entity;
    }

    void Coordinator::DestroyEntity(EntityID entity)
    {
        entityManager.DestroyEntity(entity);

        componentManager.EntityDestroyed(entity);

        systemManager.EntityDestroyed(entity);

        entities[entity] = entities.back();
        entities.pop_back();

        for (auto& node : sceneMap[entity].children)
        {
            node->parent = nullptr;
        }
        sceneMap.erase(entity);
    }

    std::vector<EntityID> Coordinator::GetEntitiesList() const
    {
        return entities;
    }

    Signature Coordinator::GetEntitySignature(EntityID entity)
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

    std::vector<EntityID> Coordinator::GetRootEntities()
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