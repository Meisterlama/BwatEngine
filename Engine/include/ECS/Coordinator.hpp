#ifndef ENGINE_ECS_COORDINATOR_HPP
#define ENGINE_ECS_COORDINATOR_HPP

#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"

namespace BwatEngine
{
    struct SceneNode
    {
        SceneNode* parent = nullptr;
        Entity id = -1;
        std::vector<SceneNode*> children{};
    };

    class Coordinator
    {
        std::unique_ptr<ComponentManager> componentManager;
        std::unique_ptr<EntityManager> entityManager;
        std::unique_ptr<SystemManager> systemManager;

        std::unordered_map<Entity, SceneNode> sceneMap;

        Coordinator() = default;
        ~Coordinator()
        {
            Coordinator* coordinator = GetInstance();
            if (coordinator)
                delete coordinator;
        }


        Coordinator(Coordinator& other) = delete;
        void operator=(const Coordinator&) = delete;

    public:
        static Coordinator* GetInstance()
        {
            static Coordinator* coordinator = nullptr;
            if (!coordinator)
                coordinator = new Coordinator;
            return coordinator;
        }
        void Init()
        {
            componentManager = std::make_unique<ComponentManager>();
            entityManager = std::make_unique<EntityManager>();
            systemManager = std::make_unique<SystemManager>();
        }

        Entity CreateEntity()
        {
            auto entity = entityManager->CreateEntity();
            sceneMap[entity].id = entity;
            return entity;
        }

        void DestroyEntity(Entity entity)
        {
            entityManager->DestroyEntity(entity);

            componentManager->EntityDestroyed(entity);

            systemManager->EntityDestroyed(entity);

            sceneMap[entity].parent = nullptr;
            sceneMap[entity].id = -1;
            for (auto& node : sceneMap[entity].children)
            {
                node->parent = nullptr;
            }
        }

        template<typename T>
        void RegisterComponent()
        {
            componentManager->RegisterComponent<T>();
        }

        template<typename T>
        void AddComponent(Entity entity, T component)
        {
            componentManager->AddComponent<T>(entity, component);

            auto signature = entityManager->GetSignature(entity);
            signature.set(componentManager->GetComponentType<T>(), true);
            entityManager->SetSignature(entity, signature);

            systemManager->EntitySignatureChanged(entity, signature);
        }

        template<typename T>
        void RemoveComponent(Entity entity)
        {
            componentManager->RemoveComponent<T>(entity);

            auto signature = entityManager->GetSignature(entity);
            signature.set(componentManager->GetComponentType<T>(), false);
            entityManager->SetSignature(entity, signature);

            systemManager->EntitySignatureChanged(entity, signature);
        }

        template<typename T>
        T &GetComponent(Entity entity)
        {
            return componentManager->GetComponent<T>(entity);
        }

        template<typename T>
        ComponentType GetComponentType()
        {
            return componentManager->GetComponentType<T>();
        }

        template<typename T>
        std::shared_ptr<T> RegisterSystem()
        {
            return systemManager->RegisterSystem<T>();
        }

        template<typename T>
        void SetSystemSignature(Signature signature)
        {
            systemManager->SetSignature<T>(signature);
        }

        Signature GetEntitySignature(Entity entity)
        {
            return entityManager->GetSignature(entity);
        }

        void SetParent(Entity entity, Entity parent)
        {
            if (parent == -1)
            {
                sceneMap[entity].parent = nullptr;
                return;
            }
                sceneMap[entity].parent = &sceneMap[parent];
                sceneMap[parent].children.push_back(&sceneMap[entity]);
        }

        SceneNode& GetNode(Entity entity)
        {
            return sceneMap[entity];
        }

        //TODO: Better way to get root entities
        std::vector<Entity> GetRootEntities()
        {
            std::vector<Entity> rootEntities;
            for (auto& [id, node] : sceneMap)
            {
                if (node.parent == nullptr)
                {
                    rootEntities.push_back(id);
                }
            }
            return rootEntities;
        }
    };
}
#endif //ENGINE_ECS_COORDINATOR_HPP