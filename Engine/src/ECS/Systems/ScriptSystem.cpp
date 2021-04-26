#include "ECS/Systems/ScriptSystem.hpp"
#include "ECS/Components/ScriptComponent.hpp"
#include "ECS/Coordinator.hpp"
#include "Scripting/common.hpp"

using namespace BwatEngine;


void ScriptSystem::Init()
{
    int x = 0;
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::io, sol::lib::os, sol::lib::math);

    lua.require("common",
                sol::c_call<decltype(&open_common), &open_common>,
                true);
}

void ScriptSystem::Update()
{
    for (auto entity : entities)
    {
        auto &scriptComponent = Coordinator::GetInstance().GetComponent<ScriptComponent>(entity);

        lua["entity"] = entity;
        if (!scriptComponent.isStarted)
        {
            sol::protected_function_result pfr = lua.script_file(scriptComponent.startScriptPath,
                                                                 sol::script_pass_on_error);

            if (pfr.valid())
            {
                scriptComponent.isStarted = true;
            }
            else
            {
                sol::error err = pfr;
                LogDebug("[LUA] Start script failed : %s", err.what());
            }
        }
        else
        {
            sol::protected_function_result pfr = lua.safe_script_file(scriptComponent.updateScriptPath,
                                                                      sol::script_pass_on_error);
            if (!pfr.valid())
            {
                sol::error err = pfr;
                LogDebug("[LUA] Start script failed : %s", err.what());
            }
        }
    }

    lua.collect_garbage();
}