#include <string>
#include "ECS/Coordinator.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/DataComponent.hpp"
#include "ECS/Components/AudioSourceComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/LightComponent.hpp"
#include "ECS/Components/PlayerComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/ScriptComponent.hpp"

#include "ResourceManager/ResourceManager.hpp"

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
            AddComponent<DataComponent>(entity, {});

            std::string entityName = "Entity_" + std::to_string(entity);
            GetComponent<DataComponent>(entity).name = entityName;

            return entity;
    }

    EntityID Coordinator::DuplicateEntity(EntityID entity)
    {
        EntityID newEntity = CreateEntity();
#define CHECK_AND_COPY_COMP(component) \
        if (HaveComponent<component>(entity)) \
        { \
            AddComponent<component>(newEntity, GetComponent<component>(entity)); \
        }

        CHECK_AND_COPY_COMP(AudioSourceComponent);
        CHECK_AND_COPY_COMP(CameraComponent);
        CHECK_AND_COPY_COMP(LightComponent);
        CHECK_AND_COPY_COMP(PlayerComponent);
        CHECK_AND_COPY_COMP(ScriptComponent);
        CHECK_AND_COPY_COMP(TransformComponent);

        if(HaveComponent<RenderableComponent>(entity))
        {
            AddComponent<RenderableComponent>(newEntity);
            auto& entityModel = GetComponent<RenderableComponent>(entity).model;
            if (entityModel)
            {
                Rendering::Model* model = ResourceManager::Instance()->GetOrLoadModel(entityModel->modelPath);
                GetComponent<RenderableComponent>(newEntity).model = model;
            }
        }

#undef CHECK_AND_COPY_COMP
        return newEntity;
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