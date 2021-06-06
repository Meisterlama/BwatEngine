#include "Serialization/Serialization.hpp"
#include "Serialization/SerializeComponent.hpp"
#include "Serialization/LoadComponent.hpp"

#include "Time.hpp"

#include "ECS/Coordinator.hpp"
#include <fstream>

namespace BwatEngine::Serialization {

    void SaveScene(fs::path path)
    {
        LogInfo("[Serial] Saving scene at path: %s", path.c_str());
        std::ofstream file(path);

        file << SerializeScene().dump(2) << std::endl;
    }

    void LoadScene(fs::path path)
    {
        LogInfo("[Serial] Loading scene at path: %s", path.c_str());
        std::ifstream file(path);

        if (!file)
        {
            LogError("[Serial] No File at path :%s", path.c_str());
            return;
        }

        json js;
        file >> js;
        DeserializeScene(js);
    }

    json SaveEntity(EntityID entityID)
    {
        json ret;
        Serialization::SaveComponent<TransformComponent>(entityID, ret);
        Serialization::SaveComponent<CameraComponent>(entityID, ret);
        Serialization::SaveComponent<RigidBodyComponent>(entityID, ret);
        Serialization::SaveComponent<RenderableComponent>(entityID, ret);
        Serialization::SaveComponent<ColliderComponent>(entityID, ret);
        Serialization::SaveComponent<ScriptComponent>(entityID, ret);
        Serialization::SaveComponent<LightComponent>(entityID, ret);
        Serialization::SaveComponent<DataComponent>(entityID, ret);
        Serialization::SaveComponent<AudioSourceComponent>(entityID, ret);
        Serialization::SaveComponent<ListenerComponent>(entityID, ret);
//          Serialization::SaveComponent<AnimatorComponent>(entityID, ret);

        return ret;
    }

    EntityID LoadEntity(json entityData)
    {
        Coordinator &coordinator = Coordinator::GetInstance();
        auto newEntity =  coordinator.CreateEntity();

        for (auto component : entityData)
        {
            auto componentId = component["Type"];
            auto componentData = component["Data"];
            if (componentId == "transform")
                Serialization::Load<TransformComponent>(newEntity, componentData);
            else if (componentId == "camera")
                Serialization::Load<CameraComponent>(newEntity, componentData);
            else if (componentId == "rigidbody")
                Serialization::Load<RigidBodyComponent>(newEntity, componentData);
            else if (componentId == "renderable")
                Serialization::Load<RenderableComponent>(newEntity, componentData);
            else if (componentId == "collider")
                Serialization::Load<ColliderComponent>(newEntity, componentData);
            else if (componentId == "script")
                Serialization::Load<ScriptComponent>(newEntity, componentData);
            else if (componentId == "light")
                Serialization::Load<LightComponent>(newEntity, componentData);
            else if (componentId == "data")
                Serialization::Load<DataComponent>(newEntity, componentData);
            else if (componentId == "audio")
                Serialization::Load<AudioSourceComponent>(newEntity, componentData);
            else if (componentId == "listener")
                Serialization::Load<ListenerComponent>(newEntity, componentData);
//               else if (componentId == "animator")
//                   Serialization::Load<AnimatorComponent>(newEntity, componentData);
        }

        return newEntity;
    }

    void SavePrefab(EntityID entityID, fs::path path)
    {
        std::ofstream file(path);

        file << SaveEntity(entityID).dump(2);
    }

    EntityID LoadPrefab(fs::path path)
    {
        std::ifstream file(path);

        if (!file)
        {
            LogError("[Serial] No File at path :%s", path);
            return 0;
        }

        json js;
        file >> js;

        return LoadEntity(js);
    }
    json SerializeScene()
    {
        json js;
        Coordinator &coordinator = Coordinator::GetInstance();
        auto entities = coordinator.GetEntitiesList();

        for (auto entity: entities)
        {
            js["Entity"].push_back(SaveEntity(entity));
        }

        return std::move(js);
    }
    void DeserializeScene(json sceneData)
    {
        Coordinator &coordinator = Coordinator::GetInstance();
        coordinator.DestroyAllEntities();
        json& entities = sceneData["Entity"];

        for (auto &entity : entities)
        {
            LoadEntity(entity);
        }

        Time::Reset();
    }
}
