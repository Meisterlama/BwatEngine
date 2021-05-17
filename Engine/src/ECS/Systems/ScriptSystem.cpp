#include "ECS/Systems/ScriptSystem.hpp"
#include "ECS/Components/ScriptComponent.hpp"
#include "ECS/Coordinator.hpp"
#include "Scripting/modules.hpp"

using namespace BwatEngine;

int setLuaPath(lua_State *L, const char *path)
{
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "path"); // get field "path" from table at top of stack (-1)
    std::string cur_path = lua_tostring(L, -1); // grab path string from top of stack
    cur_path.append(";"); // do your path magic here
    cur_path.append(path);
    lua_pop(L, 1); // get rid of the string on the stack we just pushed on line 5
    lua_pushstring(L, cur_path.c_str()); // push the new one
    lua_setfield(L, -2, "path"); // set the field "path" in table at -2 with value at top of stack
    lua_pop(L, 1); // get rid of package table from top of stack
    return 0; // all done!
}

ScriptSystem::ScriptSystem()
{
    int x = 0;
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::io, sol::lib::os);

#define REQUIRE_MODULE(module, open_module)\
lua.require(module,sol::c_call<decltype(&(open_module)), &(open_module)>,false);

    REQUIRE_MODULE("input", open_input);
    REQUIRE_MODULE("common", open_common);
    REQUIRE_MODULE("math", open_math);
    REQUIRE_MODULE("components", open_components);
    setLuaPath(lua, "./Assets/script/?.lua");
}

void ScriptSystem::Update()
{
    for (auto entity : entities)
    {
        auto &scriptComponent = Coordinator::GetInstance().GetComponent<ScriptComponent>(entity);

        lua["Start"] = sol::nil;
        lua["Update"] = sol::nil;
        auto loaded_script = lua.script_file(scriptComponent.scriptPath, sol::script_pass_on_error);

        if (scriptComponent.waitingForChanges && scriptComponent.oldPath == scriptComponent.scriptPath)
            continue;

        if (scriptComponent.oldPath != scriptComponent.scriptPath)
        {
            scriptComponent.oldPath = scriptComponent.scriptPath;
            scriptComponent.isStarted = false;
        }

        if (!loaded_script.valid())
        {
            sol::error err = loaded_script;
            scriptComponent.oldPath = scriptComponent.scriptPath;
            scriptComponent.waitingForChanges = true;
            scriptComponent.isStarted = false;
            LogDebug("[LUA] Failed to load script : %s", err.what());
            continue;
        }
        else
        {
            scriptComponent.waitingForChanges = false;
        }

        lua["entity"] = entity;

        auto startFunction = lua["Start"];
        auto updateFunction = lua["Update"];

        if (startFunction.valid() && !scriptComponent.isStarted)
        {
            auto result = startFunction();
            if (result.valid())
            {
                scriptComponent.isStarted = true;
            }
            else
            {
                sol::error err = result;
                LogDebug("[LUA] Error while calling Start on entity %i: %s", entity, err.what());
            }
            continue;
        }

        if (updateFunction.valid())
        {
            auto result = updateFunction();
            if (!result.valid())
            {
                sol::error err = result;
                LogDebug("[LUA] Error while calling Update on entity %i: %s", entity, err.what());
            }
        }
    }
    lua.collect_garbage();
}
