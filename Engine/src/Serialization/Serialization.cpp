#include "Serialization/Serialization.hpp"
#include "Scene.hpp"
#include "json.hpp"
#include "ECS/Coordinator.hpp"
#include <fstream>
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "iomanip"
#include "Debug/Logger.hpp"

#include "Serialization/SerializeComponent.hpp"

namespace BwatEngine {

    void Serializer::SaveScene(const BwatEngine::Scene &toSave, const char* path)
    {
        std::ofstream file(path);

        json js;
        Coordinator &coordinator = Coordinator::GetInstance();


        for (int i = 0; i < toSave.entities.size(); i++)
        {
            TransformComponent transform = coordinator.GetComponent<TransformComponent>(toSave.entities[i]);
            Serializable::SaveComponent<TransformComponent>(transform, js["Entity"]);


        }

            file << std::setw(4) << js << std::endl;
    }

        void Serializer::LoadScene(Scene &toLoad, const char* path)
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


            for (int i = 0; i < toLoad.entities.size(); i++) {

                json transform  = js["Entity"][i]["transform"];
                json position   = transform.at("position");
                json rotation   = transform.at("rotation");
                json scale      = transform.at("scale");

                coordinator.GetComponent<TransformComponent>(toLoad.entities[i]) = {Math::Transform{
                        Math::Vec3f{position.at("X").get<float>(), position.at("Y").get<float>(),position.at("Z").get<float>()},
                        Math::Vec3f{rotation.at("X").get<float>(),rotation.at("Y").get<float>(),rotation.at("Z").get<float>()},
                        Math::Vec3f{scale.at("X").get<float>(), scale.at("Y").get<float>(), scale.at("Z").get<float>()}
                }};
            }

        }
// all the component + data

// rigid body save as : exist


//


}
