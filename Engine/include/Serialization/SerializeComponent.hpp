#ifndef ENGINE_SERIALIZECOMPONENT_HPP
#define ENGINE_SERIALIZECOMPONENT_HPP

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

namespace BwatEngine
{

namespace Serializable
{
    template<typename T>
    void SaveComponent(T, json& js)
    {
    }

    template<>
    void
    SaveComponent<BwatEngine::TransformComponent>(TransformComponent transform, json& js)
    {
        js +=
                json{
                        {"transform",
                                {
                                        {"position",
                                                {
                                                        {"X", transform.position.X},
                                                        {"Y", transform.position.Y},
                                                        {"Z", transform.position.Z}
                                                },
                                        },
                                        {"rotation",
                                                {
                                                        {"X", transform.rotation.X},
                                                        {"Y", transform.rotation.Y},
                                                        {"Z", transform.rotation.Z}
                                                },
                                        },
                                        {"scale",
                                                {
                                                        {"X", transform.scale.X},
                                                        {"Y", transform.scale.Y},
                                                        {"Z", transform.scale.Z}
                                                }
                                        }
                                }
                        }
                };

    };
};
};

#endif