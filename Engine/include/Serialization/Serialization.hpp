#ifndef ENGINE_SERIALIZATION_HPP
#define ENGINE_SERIALIZATION_HPP

#include "json.hpp"
#include "ECS/ECS.hpp"

#include "Serialization/SerializeComponent.hpp"
#include "Serialization/LoadComponent.hpp"

namespace BwatEngine::Serialization
{
    using json = nlohmann::json;

    void SaveScene(fs::path path);
    void LoadScene(fs::path path);

    json SerializeScene();
    void DeserializeScene(json sceneData);

    json SaveEntity(EntityID entityID);
    EntityID LoadEntity(json entityData);

    void SavePrefab(EntityID entityID, fs::path path);
    EntityID LoadPrefab(fs::path path);
};

#endif //ENGINE_SERIALIZATION_HPP

