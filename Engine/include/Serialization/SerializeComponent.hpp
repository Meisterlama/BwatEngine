#ifndef ENGINE_SERIALIZECOMPONENT_HPP
#define ENGINE_SERIALIZECOMPONENT_HPP

#include <ECS/Components/RigidBodyComponent.hpp>
#include "ECS/Coordinator.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/PlayerComponent.hpp"
#include "ECS/Components/ColliderComponent.hpp"
#include "ResourceManager/ResourceManager.hpp"

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

namespace BwatEngine {

    namespace Serializable {


        json SerializeVector3f(const char* vectorName, const Math::Vec3f& vector)
        {
            return  json{
                            vectorName,
                            {
                                {"X", vector.X},
                                {"Y", vector.Y},
                                {"Z", vector.Z}
                            }
                            };
        }

        json SerializeVector4f(const char* vectorName, const Math::Vec4f& vector)
        {
            return json{
                    SerializeVector3f(vectorName, {vector.X, vector.Y, vector.Z}),
                    "W", vector.W
            };
        }

        json SerializeVector4f(const char* vectorName, const Math::Quatf& vector)
        {
            return json{
                    vectorName,
                    {
                        {"X", vector.X},
                        {"Y", vector.Y},
                        {"Z", vector.Z},
                        {"W", vector.W}
                    }
            };
        }

        template<typename T>
        void SerializeComponent(const T &, json &js) {
        }

        template<typename T>
        void SaveComponent(EntityID entityId, json &js) {
            auto &coordinator = Coordinator::GetInstance();
            if (coordinator.HaveComponent<T>(entityId))
                Serializable::SerializeComponent<T>(coordinator.GetComponent<T>(entityId), js);

        }

        template<>
        void SerializeComponent<BwatEngine::TransformComponent>(const TransformComponent &transform, json &js)
        {
            js +=
                json{
                    "transform",
                    {
                        SerializeVector3f("position", transform.position),
                        SerializeVector4f("rotation", transform.rotation.GetSafeNormalized()),
                        SerializeVector3f("scale", transform.scale)
                    }
                };
        }



        template<>
        void SerializeComponent<CameraComponent>(const CameraComponent &camera, json &js) {
            if (camera.isOrtho) {
                js +=
                        json{
                                "camera",
                                {
                                    {"ortho", camera.isOrtho},
                                    {"left", camera.left},
                                    {"right", camera.right},
                                    {"bottom", camera.bottom},
                                    {"top", camera.top},
                                    {"near", camera.near},
                                    {"far", camera.far}
                                }

                        };
            } else {
                js +=
                        json{
                                "camera",
                                {
                                    {"ortho", camera.isOrtho},
                                    {"fov", camera.fov},
                                    {"aspect", camera.aspect},
                                    {"near", camera.near},
                                    {"far", camera.far}
                                }

                        };
            }

        }

        template<>
        void SerializeComponent<PlayerComponent>(const PlayerComponent &player, json &js) {
            js += json{"player"};
        }

        template<>
        void SerializeComponent<BwatEngine::RigidBodyComponent>(const RigidBodyComponent &rigidBody, json &js) {
            js += json{"rigidBody"};
        }

        template<>
        void SerializeComponent<RenderableComponent>(const RenderableComponent &renderable, json &js) {

            json temp;
            for (int i = 0; i < renderable.materials.size(); i++) {
                Rendering::Material *material = renderable.materials[i];
                if (material->diffuse != nullptr) {
                    temp["materials"] +=
                            json{
                                    {"diffuse", material->diffuse->path}
                            };
                }
                if (material->specular != nullptr) {
                    temp["materials"] +=
                            json{
                                    {"specular", material->specular->path}
                            };
                }

            }

            if (renderable.model != nullptr) {
                temp["model"] = renderable.model->modelPath;

            }


            js += json{"renderable", temp};


        }

        template<>
        void SerializeComponent<ColliderComponent>(const ColliderComponent &collider, json &js) {

            auto *shape = collider.collider->GetShape();
            auto *mats = collider.collider->GetMaterial();
            js +=
                    json{
                            "collider",
                            {
                                    {"shape",
                                     ""}, //TODO: add the correct Shape when the collider class allow us to get it
                                    {"materials",
                                     {
                                             {"dynamic", mats->getDynamicFriction()},
                                             {"static", mats->getStaticFriction()},
                                             {"restitution", mats->getRestitution()}
                                     }
                                    }
                            }
                    };
        }


        //*********************** LOAD FUNCTIONS ***********************//
        template<typename T>
        void Load(EntityID entityId, const json &componentData) {

        }

        template<>
        void Load<TransformComponent>(EntityID entityId, const json &componentData) {

            auto &coordinator = Coordinator::GetInstance();
            json position = componentData.at("position");
            json rotation = componentData.at("rotation");
            json scale = componentData.at("scale");

            coordinator.AddComponent<TransformComponent>(entityId,
                                                         Math::Vec3f{position.at("X").get<float>(),
                                                                     position.at("Y").get<float>(),
                                                                     position.at("Z").get<float>()},
                                                         Math::Quatf {rotation.at("W").get<float>(),
                                                                     rotation.at("X").get<float>(),
                                                                     rotation.at("Y").get<float>(),
                                                                     rotation.at("Z").get<float>()},
                                                         Math::Vec3f{scale.at("X").get<float>(),
                                                                     scale.at("Y").get<float>(),
                                                                     scale.at("Z").get<float>()});

        }

        template<>
        void Load<CameraComponent>(EntityID entityId, const json &componentData) {
            auto &coordinator = Coordinator::GetInstance();
            bool isOrtho = componentData.at("ortho").get<bool>();
            if (isOrtho) {
                coordinator.AddComponent<CameraComponent>(entityId,
                                                          {isOrtho,
                                                           componentData.at("near").get<float>(),
                                                           componentData.at("far").get<float>(),
                                                           componentData.at("left").get<float>(),
                                                           componentData.at("right").get<float>(),
                                                           componentData.at("top").get<float>(),
                                                           componentData.at("bottom").get<float>(),
                                                           0,
                                                           0,
                                                          });
            } else {
                coordinator.AddComponent<CameraComponent>(entityId,
                                                          {isOrtho,
                                                           componentData.at("near").get<float>(),
                                                           componentData.at("far").get<float>(),
                                                           0,
                                                           0,
                                                           0,
                                                           0,
                                                           componentData.at("aspect").get<float>(),
                                                           componentData.at("fov").get<float>(),
                                                          });
            }

        }

        template<>
        void Load<PlayerComponent>(EntityID entityId, const json &componentData) {
            auto &coordinator = Coordinator::GetInstance();
            coordinator.AddComponent<PlayerComponent>(entityId, {});
        }

        template<>
        void Load<RigidBodyComponent>(EntityID entityId, const json &componentData) {
            auto &coordinator = Coordinator::GetInstance();
            auto eTransform = coordinator.GetComponent<TransformComponent>(entityId);
            coordinator.AddComponent<RigidBodyComponent>(entityId, eTransform, true);
        }

        template<>
        void Load<RenderableComponent>(EntityID entityId, const json &componentData) {
            auto &coordinator = Coordinator::GetInstance();
            auto *resourceMan = ResourceManager::Instance();
            coordinator.AddComponent<RenderableComponent>(entityId, {});
            auto &renderable = coordinator.GetComponent<RenderableComponent>(entityId);
            if (componentData.contains("model"))
                renderable.model = resourceMan->GetOrLoadModel(componentData.at("model").get<std::string>());

            if (componentData.contains("materials")) {
                json materials = componentData.at("materials");
                for (int i = 0; i < materials.size(); i++) {
                    if (materials.contains("diffuse")) {
                        renderable.materials[i]->SetDiffuse(
                                *resourceMan->GetOrLoadTexture(materials.at("diffuse").get<std::string>(),
                                                               Rendering::Texture::Type::E_DIFFUSE));
                    } else if (materials.contains("specular")) {

                    }
                }

            }

        }

        template<>
        void Load<ColliderComponent>(EntityID entityId, const json &componentData) {
            auto &coordinator = Coordinator::GetInstance();
            json mats = componentData.at("materials");
            auto eTransform = coordinator.GetComponent<TransformComponent>(entityId);
            coordinator.AddComponent<ColliderComponent>(entityId, {new BoxCollider{eTransform.scale}});
            auto collider = coordinator.GetComponent<ColliderComponent>(entityId);
            collider.collider->SetFriction(mats.at("static").get<float>());

        }




    }; // namespace Serializable
}; // namespace BwatEngine

#endif