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
        std::string startScriptPath;
        std::string updateScriptPath;


        bool isStarted = false;

        ScriptComponent(std::string startScriptPath, std::string updateScriptPath)
        : startScriptPath(std::move(startScriptPath))
        , updateScriptPath(std::move(updateScriptPath))
        {}
    };
}

#endif //SCRIPT_COMPONENT_HPP