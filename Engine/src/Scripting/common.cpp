#include "Scripting/modules.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/TransformComponent.hpp"

namespace BwatEngine
{
    void SetPosition(int entity, Math::Vec3f position)
    {
        auto &transform = Coordinator::GetInstance().GetComponent<TransformComponent>(entity);
        transform.position = position;
    }

    Math::Vec3f GetPosition(int entity)
    {
        return Coordinator::GetInstance().GetComponent<TransformComponent>(entity).position;
    }

    void Log(std::string logString)
    {
        LogDebug("[LUA] %s", logString.c_str());
    }

    EntityID CreateEntity()
    {
        return Coordinator::GetInstance().CreateEntity();
    }

    sol::table open_common(sol::this_state s)
    {
        sol::state_view lua(s);

        sol::table module = lua.create_table();

        module["entity"] = 0;
        module.set_function("__Log", Log);
        module.set_function("SetPosition", SetPosition);
        module.set_function("GetPosition", GetPosition);
        module.set_function("CreateEntity", CreateEntity);
        
        return module;
    }
}