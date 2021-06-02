#include "Serialization/Serialization.hpp"
#include "Serialization/SerializeComponent.hpp"
#include "Serialization/LoadComponent.hpp"

#include "ECS/Coordinator.hpp"
#include <fstream>

namespace BwatEngine::Serialization {

    void SaveScene(const char* path)
    {
        LogInfo("[Serial] Saving scene at path: %s", path);
        std::ofstream file(path);

        json js;
        Coordinator &coordinator = Coordinator::GetInstance();
        auto entities = coordinator.GetEntitiesList();

        for (auto entity: entities)
        {
            js["Entity"].push_back(SaveEntity(entity));
        }

        file << js.dump(2) << std::endl;
    }

    void LoadScene(const char* path)
    {
        LogInfo("[Serial] Loading scene at path: %s", path);
        std::ifstream file(path);

        if (!file)
        {
            LogError("[Serial] No File at path :%s", path);
            return;
        }

        json js;
        file >> js;

        Coordinator &coordinator = Coordinator::GetInstance();
        coordinator.DestroyAllEntities();
        json& entities = js["Entity"];

        for (auto &entity : entities)
        {
            LoadEntity(entity);
        }
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
            else if (componentId == "rigidBody")
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
//               else if (componentId == "animator")
//                   Serialization::Load<AnimatorComponent>(newEntity, componentData);
        }

        return newEntity;
    }

    void SavePrefab(EntityID entityID, const char *path)
    {
        std::ofstream file(path);

        file << SaveEntity(entityID).dump(2);
    }

    EntityID LoadPrefab(const char *path)
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
}
