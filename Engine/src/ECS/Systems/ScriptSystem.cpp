#include "ECS/Systems/ScriptSystem.hpp"
#include "ECS/Components/ScriptComponent.hpp"
#include "ECS/Coordinator.hpp"

using namespace BwatEngine;

void ScriptSystem::Init()
{

}

void ScriptSystem::Update()
{
	for (auto entity : entities)
	{
		auto& scriptComponent = Coordinator::GetInstance().GetComponent<ScriptComponent>(entity);

		scriptComponent.script->Update();
	}
}