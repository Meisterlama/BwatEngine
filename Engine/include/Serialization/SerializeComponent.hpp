#ifndef ENGINE_SERIALIZECOMPONENT_HPP
#define ENGINE_SERIALIZECOMPONENT_HPP

#include "ECS/Coordinator.hpp"
#include "ECS/Components/RigidBodyComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/PlayerComponent.hpp"
#include "ECS/Components/ColliderComponent.hpp"
#include "ECS/Components/AudioSourceComponent.hpp"
#include "ECS/Components/ScriptComponent.hpp"
#include "ECS/Components/LightComponent.hpp"
#include "ECS/Components/DataComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/AnimatorComponent.hpp"
#include "ResourceManager/ResourceManager.hpp"

#include "Serialization/Utils.hpp"



using json = nlohmann::json;

namespace BwatEngine::Serialization
{

    template<typename T>
    json SerializeComponent(const T &) {
        return {};
    };

    template<>
    json SerializeComponent<TransformComponent>(const TransformComponent&);
    template<>
    json SerializeComponent<CameraComponent>(const CameraComponent&);
    template<>
    json SerializeComponent<RigidBodyComponent>(const RigidBodyComponent&);
    template<>
    json SerializeComponent<RenderableComponent>(const RenderableComponent&);
    template<>
    json SerializeComponent<ColliderComponent>(const ColliderComponent&);
    template<>
    json SerializeComponent<ScriptComponent>(const ScriptComponent&);
    template<>
    json SerializeComponent<AudioSourceComponent>(const AudioSourceComponent&);
    template<>
    json SerializeComponent<LightComponent>(const LightComponent&);
    template<>
    json SerializeComponent<DataComponent>(const DataComponent&);

    template<typename T>
    void SaveComponent(EntityID entityID, json& js)
    {
        auto &coordinator = Coordinator::GetInstance();
        if (coordinator.HaveComponent<T>(entityID))
            js += SerializeComponent<T>(coordinator.GetComponent<T>(entityID));
    }
}; // namespace BwatEngine::Serialization

#endif //ENGINE_SERIALIZECOMPONENT_HPP