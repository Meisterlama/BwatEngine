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

    /**
     * @brief Singleton managing everything related to the ECS
     */
    class Coordinator
    {
				// Why are you using ptr ?
        std::unique_ptr<ComponentManager> componentManager;
        std::unique_ptr<EntityManager> entityManager;
        std::unique_ptr<SystemManager> systemManager;

        std::unordered_map<Entity, SceneNode> sceneMap;

        Coordinator() = default;

				// should be in .cpp
        ~Coordinator()
        {
            Coordinator* coordinator = GetInstance();
            if (coordinator)
                delete coordinator;
        }


        Coordinator(Coordinator& other) = delete;
        void operator=(const Coordinator&) = delete;

    public:
        /**
         * @return A handle to the Coordinator instance
         */
        static Coordinator* GetInstance()
        {
						// your singleton memory management is not reliable
						// why are you using a ptr ?
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

        /**
         * @brief Find a valid entity ID, reserve it and return it
         * @return The created entity ID
         */
        Entity CreateEntity()
        {
            auto entity = entityManager->CreateEntity();
            sceneMap[entity].id = entity;
            return entity;
        }

        /**
         * @brief Destroy the given \p entity from every managers, removing it from the scene hierarchy
         * @param entity Entity ID
         * @warning Destroying non existing entity result in undefined behavior
         */
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

        /**
         * @brief Register the component of type \p T to the ComponentManager
         * @tparam T Component type to register
         * @warning Registering a component twice is invalid
         */
        template<typename T>
        void RegisterComponent()
        {
            componentManager->RegisterComponent<T>();
        }

        /**
         * @brief Add a component \T to the given \p entity
         * @tparam T Added component's type
         * @param entity Entity ID
         * @param component Component's data (existing one or in place constructor)
         * @warning Adding a component that an entity already has is invalid
         */
        template<typename T>
        void AddComponent(Entity entity, T&& component)
        {
            componentManager->AddComponent<T>(entity, std::forward<T>(component));

            auto signature = entityManager->GetSignature(entity);
            signature.set(componentManager->GetComponentType<T>(), true);
            entityManager->SetSignature(entity, signature);

            systemManager->EntitySignatureChanged(entity, signature);
        }

        /**
         * @brief Remove the component \p T from the given \p entity
         * @tparam T Removed component's type
         * @param entity Entity ID
         * @warning Removing inexistant component is not valid
         */
        template<typename T>
        void RemoveComponent(Entity entity)
        {
            componentManager->RemoveComponent<T>(entity);

            auto signature = entityManager->GetSignature(entity);
            signature.set(componentManager->GetComponentType<T>(), false);
            entityManager->SetSignature(entity, signature);

            systemManager->EntitySignatureChanged(entity, signature);
        }

        /**
         * @brief Get the component \p T from the \p entity
         * @tparam T Type of the component to get
         * @param entity Entity ID
         * @return A reference to the component
         */
        template<typename T>
        T &GetComponent(Entity entity)
        {
            return componentManager->GetComponent<T>(entity);
        }

        /**
         * @tparam T Component's type
         * @return The component's internal ID
         */
        template<typename T>
        ComponentType GetComponentType()
        {
            return componentManager->GetComponentType<T>();
        }

        /**
         * @brief Register the system to the internal manager
         * @tparam T System's type
         * @return A pointer to the registered system
         */
        template<typename T>
        std::shared_ptr<T> RegisterSystem()
        {
            return systemManager->RegisterSystem<T>();
        }

        /**
         * @brief Set the accepted \p signature for the given system
         * @tparam T System's type
         * @param signature Signature accepted by the system
         */
        template<typename T>
        void SetSystemSignature(Signature signature)
        {
            systemManager->SetSignature<T>(signature);
        }

        /**
         * @param entity Entity ID
         * @return The signature of the given \p entity
         */
        Signature GetEntitySignature(Entity entity)
        {
            return entityManager->GetSignature(entity);
        }

        /**
         * @brief Set the parent entity in the internal scene graph
         * @param entity Entity ID
         * @param parent Parent entity ID
         */
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

        /**
         * @param entity Entity ID
         * @return Get the scene graph's node associated to entity
         */
        SceneNode& GetNode(Entity entity)
        {
            return sceneMap[entity];
        }


        //TODO: Better way to get root entities
        /**
         * @return A std::vector of every entities that does not have a parent
         * @warning Current implementation iterates over every entities without caching
         */
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
