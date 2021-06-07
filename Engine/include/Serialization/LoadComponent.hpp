#ifndef ENGINE_LOADCOMPONENT_HPP
#define ENGINE_LOADCOMPONENT_HPP

#include "Utils.hpp"

#include "ECS/Coordinator.hpp"
#include "ECS/Components/RigidBodyComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/ListenerComponent.hpp"
#include "ECS/Components/ColliderComponent.hpp"
#include "ECS/Components/AudioSourceComponent.hpp"
#include "ECS/Components/ScriptComponent.hpp"
#include "ECS/Components/LightComponent.hpp"
#include "ECS/Components/DataComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/AnimatorComponent.hpp"
#include "ECS/Components/Image2DComponent.hpp"
#include "ResourceManager/ResourceManager.hpp"

namespace BwatEngine::Serialization
{
    template<typename T>
    void Load(EntityID entityId, const json &componentData) {}

    template<>
    void Load<TransformComponent>(EntityID entityId, const json &componentData);

    template<>
    void Load<CameraComponent>(EntityID entityId, const json &componentData);

    template<>
    void Load<RigidBodyComponent>(EntityID entityId, const json &componentData);

    template<>
    void Load<RenderableComponent>(EntityID entityId, const json &componentData);

    template<>
    void Load<ColliderComponent>(EntityID entityId, const json &componentData);

    template<>
    void Load<ScriptComponent>(EntityID entityId, const json &componentData);

    template<>
    void Load<AudioSourceComponent>(EntityID entityId, const json &componentData);

    template<>
    void Load<LightComponent>(EntityID entityId, const json &componentData);

    template<>
    void Load<DataComponent>(EntityID entityId, const json &componentData);

    template<>
    void Load<AnimatorComponent>(EntityID entityId, const json& componentData);

    template<>
    void Load<ListenerComponent>(EntityID entityId, const json &componentData);

    template<>
    void Load<Image2DComponent>(EntityID entityId, const json &componentData);

}
#endif //ENGINE_LOADCOMPONENT_HPP