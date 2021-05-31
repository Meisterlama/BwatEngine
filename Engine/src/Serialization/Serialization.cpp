#include "Serialization/Serialization.hpp"
#include "Scene.hpp"
#include "json.hpp"
#include "ECS/Coordinator.hpp"
#include <fstream>
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/AnimatorComponent.hpp"
#include "iomanip"
#include "Debug/Logger.hpp"

#include "Serialization/SerializeComponent.hpp"

namespace BwatEngine {

    void Serializer::SaveScene(const char* path)
    {
        std::ofstream file(path);

        json js;
        Coordinator &coordinator = Coordinator::GetInstance();
        auto entities = coordinator.GetEntitiesList();

        // save Transform / rigidBody / Camera 
        for (int i = 0; i < entities.size(); i++)
        {
            EntityID currentEntity = entities[i];
            Serializable::SaveComponent<TransformComponent>(currentEntity, js["Entity"][i]);
            Serializable::SaveComponent<CameraComponent>(currentEntity, js["Entity"][i]);
            Serializable::SaveComponent<PlayerComponent>(currentEntity, js["Entity"][i]);
            Serializable::SaveComponent<RigidBodyComponent>(currentEntity, js["Entity"][i]);
            Serializable::SaveComponent<RenderableComponent>(currentEntity, js["Entity"][i]);
            Serializable::SaveComponent<ColliderComponent>(currentEntity, js["Entity"][i]);
            Serializable::SaveComponent<ScriptComponent>(currentEntity, js["Entity"][i]);
            Serializable::SaveComponent<LightComponent>(currentEntity, js["Entity"][i]);
            Serializable::SaveComponent<DataComponent>(currentEntity, js["Entity"][i]);
            Serializable::SaveComponent<AnimatorComponent>(currentEntity, js["Entity"][i]);
            Serializable::SaveComponent<AudioSourceComponent>(currentEntity, js["Entity"][i]);
        }

            file << std::setw(2) << js << std::endl;
    }

    void Serializer::LoadScene(const char* path)
    {
        std::ifstream file(path);


        if (!file)
        {
            LogError("No File at path :%s", path);
            return;
        }

        json js;
        file >> js;

        Coordinator &coordinator = Coordinator::GetInstance();
        coordinator.DestroyAllEntities();
        json& entities = js["Entity"];


        for (int i = 0; i < entities.size(); i++)
        {
           json& entity = entities[i];
           auto newEntity =  coordinator.CreateEntity();

           for (int j = 0; j < entity.size(); j++)
           {
               auto componentId = entity[j][0];
               auto componentData = entity[j][1];
               if (componentId == "transform")
                   Serializable::Load<TransformComponent>(newEntity, componentData);
               else if (componentId == "camera")
                   Serializable::Load<CameraComponent>(newEntity, componentData);
               else if (componentId == "player")
                   Serializable::Load<PlayerComponent>(newEntity, componentData);
               else if (componentId == "rigidBody")
                   Serializable::Load<RigidBodyComponent>(newEntity, componentData);
               else if (componentId == "renderable")
                   Serializable::Load<RenderableComponent>(newEntity, componentData);
               else if (componentId == "collider")
                   Serializable::Load<ColliderComponent>(newEntity, componentData);
               else if (componentId == "script")
                   Serializable::Load<ScriptComponent>(newEntity, componentData);
               else if (componentId == "light")
                   Serializable::Load<LightComponent>(newEntity, componentData);
               else if (componentId == "data")
                   Serializable::Load<DataComponent>(newEntity, componentData);
               else if (componentId == "audio")
                    Serializable::Load<AudioSourceComponent>(newEntity, componentData);
               else if (componentId == "animator")
                   Serializable::Load<AnimatorComponent>(newEntity, componentData);

           }

        }

    }

}
