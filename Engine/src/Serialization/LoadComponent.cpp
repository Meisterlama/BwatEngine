#include "Serialization/LoadComponent.hpp"

namespace BwatEngine::Serialization
{
    template<typename T>
    void Load(EntityID entityId, const json &componentData);

    template<>
    void Load<TransformComponent>(EntityID entityId, const json &componentData)
    {
        auto &coordinator = Coordinator::GetInstance();
        coordinator.AddComponent<TransformComponent>(entityId,
                                                     DeserializeVector3f(componentData["position"]),
                                                     DeserializeQuatf(componentData["rotation"]),
                                                     DeserializeVector3f(componentData["scale"]));

    }

    template<>
    void Load<CameraComponent>(EntityID entityId, const json &componentData)
    {
        auto &coordinator = Coordinator::GetInstance();
        bool isOrtho = componentData["ortho"];
        coordinator.AddComponent<CameraComponent>(entityId,
                                                  {isOrtho,
                                                   componentData["near"].get<float>(),
                                                   componentData["far"].get<float>(),
                                                   (isOrtho) ? componentData["left"].get<float>() : 0.0f,
                                                   (isOrtho) ? componentData["right"].get<float>() : 0.0f,
                                                   (isOrtho) ? componentData["top"].get<float>() : 0.0f,
                                                   (isOrtho) ? componentData["bottom"].get<float>() : 0.0f,
                                                   (isOrtho) ? 0.0f : componentData["aspect"].get<float>(),
                                                   (isOrtho) ? 0.0f : componentData["fov"].get<float>(),
                                                  });
    }

    template<>
    void Load<RigidBodyComponent>(EntityID entityId, const json &componentData)
    {
        auto &coordinator = Coordinator::GetInstance();
        coordinator.AddComponent<RigidBodyComponent>(entityId);
        auto &rigidBody = coordinator.GetComponent<RigidBodyComponent>(entityId);

        rigidBody.SetStatic(componentData["static"]);
        rigidBody.SetMass(componentData["mass"]);
        rigidBody.SetVelocity(DeserializeVector3f(componentData["velocity"]));
        bool lockX = (componentData.contains("lockX")) && componentData["lockX"].get<bool>();
        bool lockY = (componentData.contains("lockY")) && componentData["lockY"].get<bool>();
        bool lockZ = (componentData.contains("lockZ")) && componentData["lockZ"].get<bool>();

        rigidBody.LockRotation(lockX, lockY, lockZ);
    }

#define DESERIALIZE_TEXTURE(texture)                                      \
    if (material.contains(#texture))                                      \
        newMaterial->texture = resMan->GetOrLoadTexture(material[#texture].get<std::string>())

    template<>
    void Load<RenderableComponent>(EntityID entityId, const json &componentData)
    {
        auto &coordinator = Coordinator::GetInstance();
        auto *resMan = ResourceManager::Instance();

        coordinator.AddComponent<RenderableComponent>(entityId);
        auto &renderable = coordinator.GetComponent<RenderableComponent>(entityId);

        if (componentData.contains("model"))
            renderable.model = resMan->GetOrLoadModel(componentData["model"].get<std::string>());

        if (componentData.contains("materials"))
        {
            for (auto material : componentData["materials"])
            {
                auto newMaterial = new Rendering::Material;

                newMaterial->isTextured = material["isTextured"];

                DESERIALIZE_TEXTURE(albedoMap);
                DESERIALIZE_TEXTURE(normal);
                DESERIALIZE_TEXTURE(metallicMap);
                DESERIALIZE_TEXTURE(roughnessMap);
                DESERIALIZE_TEXTURE(aoMap);

                newMaterial->albedo = DeserializeVector3f(material["albedo"]);
                newMaterial->metallic = material["metallic"];
                newMaterial->roughness = material["roughness"];
                newMaterial->ao = material["ao"];

                newMaterial->isTilling = material["isTilling"];
                newMaterial->tile = DeserializeVector2f(material["tile"]);

                renderable.materials.push_back(newMaterial);
            }
        }
    }

#undef DESERIALIZE_TEXTURE

    template<>
    void Load<ColliderComponent>(EntityID entityId, const json &componentData)
    {
        auto &coordinator = Coordinator::GetInstance();

        coordinator.AddComponent<ColliderComponent>(entityId);
        auto &collider = coordinator.GetComponent<ColliderComponent>(entityId);

        collider.SetShape(componentData["shapeType"]);
        switch (collider.GetShapeType())
        {

            case Collider::CUBE:
                collider.SetBoxExtent(DeserializeVector3f(componentData["shapeData"]["halfExtents"]));
                break;
            case Collider::SPHERE:
                collider.SetSphereRadius(componentData["shapeData"]["radius"]);
                break;
        }

        if (componentData.contains("isTrigger"))
            collider.SetIsTrigger(componentData["isTrigger"].get<bool>());
    }

    template<>
    void Load<ScriptComponent>(EntityID entityId, const json &componentData)
    {
        auto &coordinator = Coordinator::GetInstance();
        coordinator.AddComponent<ScriptComponent>(entityId, componentData["path"]);
        ResourceManager::Instance()->GetOrLoadScript(componentData["path"]);
    }

    template<>
    void Load<AudioSourceComponent>(EntityID entityId, const json &componentData)
    {
        auto &resourceManager = *ResourceManager::Instance();
        auto &coordinator = Coordinator::GetInstance();

        coordinator.AddComponent<AudioSourceComponent>(entityId);
        auto &audioComponent = coordinator.GetComponent<AudioSourceComponent>(entityId);

        audioComponent.source.audioData = resourceManager.GetOrLoadAudio(componentData["path"].get<std::string>());
        audioComponent.source.Refresh();
        audioComponent.source.SetGain(componentData["gain"]);
        audioComponent.source.SetPitch(componentData["pitch"]);
        audioComponent.source.SetLooping(componentData["looping"]);
    }

    template<>
    void Load<LightComponent>(EntityID entityId, const json &componentData)
    {
        auto &coordinator = Coordinator::GetInstance();

        Rendering::Light myLight;
        myLight.typeoflight = componentData["lightType"];

        myLight.position = DeserializeVector3f(componentData["position"]);
        myLight.direction = DeserializeVector3f(componentData["direction"]);

        myLight.ambient = DeserializeVector3f(componentData["ambient"]);
        myLight.diffuse = DeserializeVector3f(componentData["diffuse"]);
        myLight.specular = DeserializeVector3f(componentData["specular"]);

        myLight.constant = componentData["constant"];
        myLight.linear = componentData["linear"];
        myLight.quadratic = componentData["quadratic"];

        if (myLight.typeoflight == Rendering::Spot)
        {
            myLight.cutoff = componentData["cutoff"];
            myLight.outerCutoff = componentData["outerCutoff"];
        }

        coordinator.AddComponent<LightComponent>(entityId, myLight);
    }

    template<>
    void Load<DataComponent>(EntityID entityId, const json &componentData)
    {
        auto &coordinator = Coordinator::GetInstance();
        coordinator.AddComponent<DataComponent>(entityId, componentData["name"]);
    }

    template<>
    void Load<ListenerComponent>(EntityID entityId, const json &componentData)
    {
        auto &coordinator = Coordinator::GetInstance();
        coordinator.AddComponent<ListenerComponent>(entityId);
    }
}