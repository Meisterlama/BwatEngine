#include "Serialization/Utils.hpp"

namespace BwatEngine
{
    json SerializeVector2f(const Math::Vec2f &vector)
    {
        json ret;
        ret["X"] = vector.X;
        ret["Y"] = vector.Y;
        return ret;
    }

    json SerializeVector3f(const Math::Vec3f &vector)
    {
        json ret;
        ret["X"] = vector.X;
        ret["Y"] = vector.Y;
        ret["Z"] = vector.Z;
        return ret;
    }

    json SerializeVector4f(const Math::Vec4f &vector)
    {
        json ret;
        ret["X"] = vector.X;
        ret["Y"] = vector.Y;
        ret["Z"] = vector.Z;
        ret["W"] = vector.W;
        return ret;
    }

    json SerializeQuatf(const Math::Quatf &quat)
    {
        json ret;
        ret["X"] = quat.X;
        ret["Y"] = quat.Y;
        ret["Z"] = quat.Z;
        ret["W"] = quat.W;
        return ret;
    }

    Math::Vec2f DeserializeVector2f(const json &js)
    {
        return Math::Vec2f {
            js["X"].get<float>(),
            js["Y"].get<float>(),
        };
    }

    Math::Vec3f DeserializeVector3f(const json &js)
    {
        return Math::Vec3f {
            js["X"].get<float>(),
            js["Y"].get<float>(),
            js["Z"].get<float>(),
        };
    }

    Math::Vec4f DeserializeVector4f(const json &js)
    {
        return Math::Vec4f {
                js["X"].get<float>(),
                js["Y"].get<float>(),
                js["Z"].get<float>(),
                js["W"].get<float>(),
        };
    }
    Math::Quatf DeserializeQuatf(const json &js)
    {
        return Math::Quatf {
                js["W"].get<float>(),
                js["X"].get<float>(),
                js["Y"].get<float>(),
                js["Z"].get<float>(),
        };
    }
}