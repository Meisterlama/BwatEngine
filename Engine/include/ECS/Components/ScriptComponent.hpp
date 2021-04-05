#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

class Script 
{
public :
	
	// why not make it a pure virtual (ie. virtual void foo() = 0)
	virtual void Update() {};
	virtual void Start() {};
};

namespace BwatEngine
{
	struct ScriptComponent
	{
		// initialize your ptr to nullptr
		// look at ColliderComponent.hpp comments
		Script* script;
	};
}

#endif
