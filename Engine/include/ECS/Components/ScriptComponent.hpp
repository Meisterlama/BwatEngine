#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

class Script 
{
public :
	
	virtual void Update() = 0;
	virtual void Start() = 0;
};

namespace BwatEngine
{
	struct ScriptComponent
	{
		Script* script = nullptr;
	};
}

#endif //SCRIPT_COMPONENT_HPP