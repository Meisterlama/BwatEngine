#include "Scripting/modules.hpp"

#include "Math/Math.hpp"

namespace BwatEngine
{
    sol::table open_math(sol::this_state s)
    {
        sol::state_view lua(s);

        sol::table module = lua.create_table();

        module.new_usertype<Math::Vec3f>("Vec3f",
                                         "X", &Math::Vec3f::X,
                                         "Y", &Math::Vec3f::Y,
                                         "Z", &Math::Vec3f::Z
        );

        module.new_usertype<Math::Vec3d>("Vec3d",
                                         "X", &Math::Vec3d::X,
                                         "Y", &Math::Vec3d::Y,
                                         "Z", &Math::Vec3d::Z
        );

        module.new_usertype<Math::Vec2f>("Vec2f",
                                         "X", &Math::Vec2f::X,
                                         "Y", &Math::Vec2f::Y
        );

        module.new_usertype<Math::Vec2d>("Vec2d",
                                         "X", &Math::Vec2d::X,
                                         "Y", &Math::Vec2d::Y
        );

        module.new_usertype<Math::Quatf>("Quatf",
                                         "X", &Math::Quatf::X,
                                         "Y", &Math::Quatf::Y,
                                         "Z", &Math::Quatf::Z,
                                         "W", &Math::Quatf::W
        );

        module.new_usertype<Math::Quatd>("Quatd",
                                         "X", &Math::Quatd::X,
                                         "Y", &Math::Quatd::Y,
                                         "Z", &Math::Quatd::Z,
                                         "W", &Math::Quatd::W
        );

        module.new_usertype<Math::Transform>("Transform",
                                         "position", &Math::Transform::position,
                                         "rotation", &Math::Transform::rotation,
                                         "scale", &Math::Transform::scale
        );
        return module;
    }
}