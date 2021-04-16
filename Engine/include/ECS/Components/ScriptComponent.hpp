#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

#include "ECS/ECS.hpp"
namespace BwatEngine
{

class Script 
{
public :

	bool isStarted = false;

	EntityID  entity;

	virtual void Update() = 0;
	virtual void Start() = 0;
};


	struct ScriptComponent
	{
		Script* script = nullptr;
	};
}

#endif //SCRIPT_COMPONENT_HPP