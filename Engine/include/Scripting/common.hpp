#ifndef ENGINE_SCRIPTING_COMMON_HPP
#define ENGINE_SCRIPTING_COMMON_HPP

#include <string>
#include "Math/Vector/Vector3.hpp"
#include "sol/sol.hpp"


namespace BwatEngine {
    void SetPosition(int entity, Math::Vec3f position);

    Math::Vec3f GetPosition(int entity);

    void Log(std::string logString);

    sol::table open_common(sol::this_state s);
}



#endif //ENGINE_SCRIPTING_COMMON_HPP
