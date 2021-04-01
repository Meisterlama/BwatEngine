#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

class Script 
{
public :
	
	virtual void Update() {};
	virtual void Start() {};
};

namespace BwatEngine
{
	struct ScriptComponent
	{
		Script* script;
	};
}

#endif