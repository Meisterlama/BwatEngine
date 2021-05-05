#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

#include <utility>

#include "ECS/ECS.hpp"
#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

namespace BwatEngine
{
    struct ScriptComponent
    {
    public :
        std::string scriptPath;
        std::string oldPath;

        bool isStarted = false;

        bool waitingForChanges = false;

        ScriptComponent(std::string startScriptPath = "")
        : scriptPath(std::move(startScriptPath))
        {}
    };
}

#endif //SCRIPT_COMPONENT_HPP