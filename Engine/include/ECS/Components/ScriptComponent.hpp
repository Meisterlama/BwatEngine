#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

#include "Physic/PhysicScene.hpp"

namespace BwatEngine
{
    struct ScriptComponent
    {

    public :
        std::string scriptPath;
        std::string oldPath;

        std::vector<Contact> contacts;

        bool isStarted = false;
        bool waitingForChanges = false;

        ScriptComponent(std::string startScriptPath = "")
        : scriptPath(std::move(startScriptPath))
        , oldPath(scriptPath)
        {}
    };
}

#endif //SCRIPT_COMPONENT_HPP