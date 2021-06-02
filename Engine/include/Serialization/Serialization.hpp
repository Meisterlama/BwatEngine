#ifndef ENGINE_SERIALIZATION_HPP
#define ENGINE_SERIALIZATION_HPP

#include "json.hpp"
#include "ECS/ECS.hpp"

namespace BwatEngine::Serialization
{
    using json = nlohmann::json;

    void SaveScene(const char* path);
    void LoadScene(const char* path);

    json SaveEntity(EntityID entityID);
    EntityID LoadEntity(json entityData);

    void SavePrefab(EntityID entityID, const char* path);
    EntityID LoadPrefab(const char* path);
};

#endif //ENGINE_SERIALIZATION_HPP

