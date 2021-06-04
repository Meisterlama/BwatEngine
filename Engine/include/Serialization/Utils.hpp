#ifndef ENGINE_SERIALIZATION_UTILS_HPP
#define ENGINE_SERIALIZATION_UTILS_HPP

#include "json.hpp"
#include "Math/Math.hpp"


namespace BwatEngine
{
    using json = nlohmann::json;

    json SerializeVector2f(const Math::Vec2f &vector);

    json SerializeVector3f(const Math::Vec3f &vector);

    json SerializeVector4f(const Math::Vec4f &vector);

    json SerializeQuatf(const Math::Quatf &quat);

     Math::Vec2f DeserializeVector2f(const json& js);
     Math::Vec3f DeserializeVector3f(const json& js);
     Math::Vec4f DeserializeVector4f(const json& js);
     Math::Quatf DeserializeQuatf(const json& js);
}

#endif //ENGINE_SERIALIZATION_UTILS_HPP