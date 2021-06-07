#ifndef ENGINE_ECS_COORDINATOR_HPP
#define ENGINE_ECS_COORDINATOR_HPP

#include "ECS.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"

#include "Debug/Logger.hpp"

#include "Name.hpp"

namespace BwatEngine
{
    struct SceneNode
    {
        SceneNode* parent = nullptr;
        EntityID id = 0;
        std::vector<SceneNode*> children{};
    };

    /**
     * @brief Singleton managing everything related to the ECS
     */
    class Coordinator
    {
        ComponentManager componentManager{};
        EntityManager entityManager{};
        SystemManager systemManager{};

        std::vector<EntityID> entities{};
        std::unordered_map<EntityID, SceneNode> sceneMap{};

        Coordinator()
        {
            entities.reserve(MAX_ENTITIES);
        }
        ~Coordinator() = default;

    public:

        Coordinator(Coordinator& other) = default;
        Coordinator& operator=(const Coordinator&) = default;

        /**
         * @return A handle to the Coordinator instance
         */
        static Coordinator& GetInstance();

        void ClearInstance();

        /**
         * @brief Find a valid entity ID, reserve it and return it
         * @return The created entity ID
         */
        EntityID CreateEntity();

        /**
         * @param entity Entity ID
         * @return True if the entity ID is valid
         */
        bool IsValid(EntityID entity);

        /**
         * @brief Destroy the given \p entity from every managers, removing it from the scene hierarchy
         * @param entity EntityID ID
         * @warning Destroying non existing entity result in undefined behavior
         */
        void DestroyEntity(EntityID entity);

        /**
         * @return a copy of the entity list
         */
        std::vector<EntityID> GetEntitiesList() const;

        /**
         * @param signature Entities's signature wanted
         * @return A std::vector containing all entities with a given signature
         * @warning This function iterates over **every** entities created. It should be used with care.
         */
        std::vector<EntityID> GetEntitiesWithSignature(Signature signature);

        /**
         * @param name Name of the entity wanted
         * @return A EntityID which name is equal to \p name
         * @warning If multiple entities have the same name, only the first one encountered is returned
         */
        EntityID GetEntityWithName(const std::string& name);

        /**
         * @brief Destroy all entities created with the coordinator
         */
        void DestroyAllEntities();

        /**
         * @brief Register the component of type \p C to the ComponentManager
         * @tparam C Component type to register
         * @warning Registering a component twice is invalid
         */
        template<class C>
        void RegisterComponent()
        {
            LogInfo("[ECS] Registered component %s", GetInternalName<C>().c_str());
            componentManager.RegisterComponent<C>();
        }

        /**
         * @brief Construct in place a component \p C to the given \p entity
         * @tparam C Added component's type
         * @tparam Args Entity's constructor arguments types
         * @param entity Entity's ID
         * @param args Entity's constructor arguments
         */
        template<class C, typename... Args>
        void AddComponent(EntityID entity, Args&&... args)
        {
            componentManager.AddComponent<C>(entity, std::forward<Args>(args)...);

            auto signature = entityManager.GetSignature(entity);
            signature.set(componentManager.GetComponentType<C>(), true);
            entityManager.SetSignature(entity, signature);

            systemManager.EntitySignatureChanged(entity, signature);
        }

        /**
         * @brief Add a component \C to the given \p entity
         * @tparam C Added component's type
         * @param entity EntityID ID
         * @param component Component's data (existing one)
         * @warning Adding a component that an entity already has is invalid
         */
        template<class C>
        void AddComponent(EntityID entity, C&& component)
        {
            componentManager.AddComponent<C>(entity, std::forward<C>(component));

            auto signature = entityManager.GetSignature(entity);
            signature.set(componentManager.GetComponentType<C>(), true);
            entityManager.SetSignature(entity, signature);

            systemManager.EntitySignatureChanged(entity, signature);
        }

        /**
         * @brief Add a component \p C to the given \p entity
         * @tparam C Added component's type
         * @param entity EntityID ID
         * @warning Adding a component that an entity already has is invalid
         */
        template<class C>
        void AddComponent(EntityID entity)
        {
            componentManager.AddComponent<C>(entity);

            auto signature = entityManager.GetSignature(entity);
            signature.set(componentManager.GetComponentType<C>(), true);
            entityManager.SetSignature(entity, signature);

            systemManager.EntitySignatureChanged(entity, signature);
        }

        /**
         * @brief Remove the component \p C from the given \p entity
         * @tparam C Removed component's type
         * @param entity EntityID ID
         * @warning Removing non-existent component is not valid
         */
        template<class C>
        void RemoveComponent(EntityID entity)
        {
            componentManager.RemoveComponent<C>(entity);

            auto signature = entityManager.GetSignature(entity);
            signature.set(componentManager.GetComponentType<C>(), false);
            entityManager.SetSignature(entity, signature);

            systemManager.EntitySignatureChanged(entity, signature);
        }

        /**
         * @brief Get the component \p C from the \p entity
         * @tparam C Type of the component to get
         * @param entity EntityID ID
         * @return A reference to the component
         */
        template<class C>
        C &GetComponent(EntityID entity)
        {
            return componentManager.GetComponent<C>(entity);
        }

        /**
         * @tparam C Component's type
         * @return The component's internal ID
         */
        template<class C>
        ComponentTypeID GetComponentType()
        {
            return componentManager.GetComponentType<C>();
        }

        /**
         * @brief Check if the \p entity have the component \p C
         * @tparam C Component's type
         * @param entity Entity ID
         * @return true if the entity have the component
         */
        template<class C>
        bool HaveComponent(EntityID entity)
        {
            return entityManager.GetSignature(entity).test(GetComponentType<C>());
        }

        /**
         * @brief Get the entity ID from a component reference
         * @tparam C Component's type
         * @param component Component's data
         * @return Entity's ID if found, 0 if a problem occurred
         */
        template<class C>
        EntityID GetEntityIDFrom(C& component)
        {
             return componentManager.GetEntityIDFrom(component);
        }

        /**
         * @brief Register the system to the internal manager
         * @tparam S System's type
         * @return A pointer to the registered system
         */
        template<class S, class... Args>
        std::shared_ptr<S> RegisterSystem(Args&&... args)
        {
            LogInfo("[ECS] Registered system %s", GetInternalName<S>().c_str());
            std::shared_ptr<S> systemPtr = systemManager.RegisterSystem<S>(args...);
            return systemPtr;
        }

        template<typename S>
        void SetSystemConfig(SystemConfig config)
        {
            systemManager.SetSystemConfig<S>(config);
            LogInfo("[ECS] Update %s config", GetInternalName<S>().c_str());
        }

        /**
         * @brief Set the accepted \p signature for the given system
         * @tparam S System's type
         * @param signature Signature accepted by the system
         */
        template<class S, class... C>
        constexpr void SetSystemSignature()
        {
            Signature signature;
            std::array<ComponentTypeID, sizeof...(C)> IDs = {GetComponentType<C>()...};
            for (auto ID : IDs)
            {
                signature.set(ID);
            }
            systemManager.SetSignature<S>(signature);
            LogInfo("[ECS] Update %s signature requirement", GetInternalName<S>().c_str());
        }

        void UpdateSystems(bool gameUpdate)
        {
            systemManager.UpdateSystems(gameUpdate);
        }

        template<class S>
        std::shared_ptr<S> GetSystem()
        {
              return systemManager.GetSystem<S>() ;
        }

        /**
         * @param entity EntityID ID
         * @return The signature of the given \p entity
         */
        Signature GetEntitySignature(EntityID entity) const;

        /**
         * @brief Set the parent entity in the internal scene graph
         * @param entity EntityID ID
         * @param parent Parent entity ID
         */
        void SetParent(EntityID entity, EntityID parent);

        /**
         * @param entity EntityID ID
         * @return Get the scene graph's node associated to entity
         */
        SceneNode& GetNode(EntityID entity);


        //TODO: Better way to get root entities
        /**
         * @return A std::vector of every entities that does not have a parent
         * @warning Current implementation iterates over every entities without caching
         */
        std::vector<EntityID> GetRootEntities() const;

        template <typename S>
        std::string GetInternalName()
        {
            return ECS::Internal::demangle(typeid(S).name());
        }
    };
}
#endif //ENGINE_ECS_COORDINATOR_HPP