#include "Scripting/modules.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/TransformComponent.hpp"

namespace BwatEngine
{
    void Log(std::string logString)
    {
        LogDebug("[LUA] %s", logString.c_str());
    }

    EntityID CreateEntity()
    {
        return Coordinator::GetInstance().CreateEntity();
    }

    void DestroyEntity(EntityID entity)
    {
        Coordinator::GetInstance().DestroyEntity(entity);
    }

    EntityID GetEntityByName(std::string name)
    {
        return Coordinator::GetInstance().GetEntityWithName(name);
    }

    sol::table open_common(sol::this_state s)
    {
        sol::state_view lua(s);

        sol::table module = lua.create_table();

        module.set_function("__Log", Log);
        module.set_function("CreateEntity", CreateEntity);
        module.set_function("DestroyEntity", DestroyEntity);
        module.set_function("GetEntityByName", GetEntityByName);

        return module;
    }
}