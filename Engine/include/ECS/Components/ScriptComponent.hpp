#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

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