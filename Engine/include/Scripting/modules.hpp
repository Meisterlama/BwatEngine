#ifndef ENGINE_SCRIPTING_MODULES_HPP
#define ENGINE_SCRIPTING_MODULES_HPP

#include "sol/sol.hpp"

namespace BwatEngine {
    sol::table open_common(sol::this_state s);
    sol::table open_input(sol::this_state s);
    sol::table open_math(sol::this_state s);
    sol::table open_components(sol::this_state s);
}



#endif //ENGINE_SCRIPTING_MODULES_HPP
