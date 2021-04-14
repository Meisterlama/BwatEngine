#ifndef ENGINE_ECS_COORDINATOR_HPP
#define ENGINE_ECS_COORDINATOR_HPP

#include "ECS.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"

#include "Debug/Logger.hpp"

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

        /**
         * @brief Find a valid entity ID, reserve it and return it
         * @return The created entity ID
         */
        EntityID CreateEntity();

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
         * @brief Register the component of type \p C to the ComponentManager
         * @tparam C Component type to register
         * @warning Registering a component twice is invalid
         */
        template<class C>
        void RegisterComponent()
        {
            LogInfo("Registered component %s", typeid(C).name());
            componentManager.RegisterComponent<C>();
        }

        /**
         * @brief Add a component \C to the given \p entity
         * @tparam C Added component's type
         * @param entity EntityID ID
         * @param component Component's data (existing one or in place constructor)
         * @warning Adding a component that an entity already has is invalid
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
         * @brief Remove the component \p C from the given \p entity
         * @tparam C Removed component's type
         * @param entity EntityID ID
         * @warning Removing inexistant component is not valid
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
         * @brief Register the system to the internal manager
         * @tparam S System's type
         * @return A pointer to the registered system
         */
        template<class S>
        std::shared_ptr<S> RegisterSystem()
        {
            LogInfo("Registered system %s", typeid(S).name());
            return systemManager.RegisterSystem<S>();
        }

        /**
         * @brief Set the accepted \p signature for the given system
         * @tparam S System's type
         * @param signature Signature accepted by the system
         */
        template<class S>
        void SetSystemSignature(Signature signature)
        {
            systemManager.SetSignature<S>(signature);
        }

        /**
         * @param entity EntityID ID
         * @return The signature of the given \p entity
         */
        Signature GetEntitySignature(EntityID entity);

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
        std::vector<EntityID> GetRootEntities();
    };
}
#endif //ENGINE_ECS_COORDINATOR_HPP