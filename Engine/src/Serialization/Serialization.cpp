#include "Serialization/Serialization.hpp"
#include "Scene.hpp"
#include "json.hpp"
#include "ECS/Coordinator.hpp"
#include <fstream>
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "iomanip"
#include "Debug/Logger.hpp"


using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

namespace BwatEngine {

    Serializer::Serializer(const char *path)
            : path(path) {

    }


    void Serializer::SaveScene(const BwatEngine::Scene &toSave) {
        std::ofstream file(path);

        json js;
        Coordinator &coordinator = *Coordinator::GetInstance();


        for (int i = 0; i < toSave.entities.size(); i++)
        {
            TransformComponent transform = coordinator.GetComponent<TransformComponent>(toSave.entities[i]);
            js["Entity"] +=
                    json{
                            {"transform",
                                    {
                                            {"position",
                                                {
                                                        {"X", transform.transform.position.X},
                                                        {"Y", transform.transform.position.Y},
                                                        {"Z", transform.transform.position.Z}
                                                },
                                            },
                                            {"rotation",
                                                {
                                                    {"X", transform.transform.rotation.X},
                                                    {"Y", transform.transform.rotation.Y},
                                                    {"Z", transform.transform.rotation.Z}
                                                },
                                            },
                                            {"scale",
                                                {
                                                    {"X", transform.transform.scale.X},
                                                    {"Y", transform.transform.scale.Y},
                                                    {"Z", transform.transform.scale.Z}
                                                }
                                            }
                                    }
                            }
                    };
       }


            file << std::setw(4) << js << std::endl;
        }

        void Serializer::LoadData(Scene &toLoad) {
            std::ifstream file(path);


            json js;
            file >> js;

            Coordinator &coordinator = *Coordinator::GetInstance();


            for (int i = 0; i < toLoad.entities.size(); i++) {

                json transform = js["Entity"][i]["transform"];

                coordinator.GetComponent<TransformComponent>(toLoad.entities[i]) = {Math::Transform{
                        Math::Vec3f{transform.at("position").at("X").get<float>(), transform.at("position").at("Y").get<float>(),transform.at("position").at("Z").get<float>()},
                        Math::Vec3f{transform.at("rotation").at("X").get<float>(),transform.at("rotation").at("Y").get<float>(),transform.at("rotation").at("Z").get<float>()},
                        Math::Vec3f{transform.at("scale").at("X").get<float>(), transform.at("scale").at("Y").get<float>(), transform.at("scale").at("Z").get<float>()}
                }};
            }

        }
// all the component + data

// rigid body save as : exist


}
