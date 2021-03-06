#ifndef SCRIPT_SYSTEM_HPP
#define SCRIPT_SYSTEM_HPP

#include "ECS/System.hpp"

#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

namespace BwatEngine
{
	class ScriptSystem : public System
	{
	private:
        sol::state lua;
	public:

        ScriptSystem();
		virtual void Update() override;
	};
}

#endif // SCRIPT_SYSTEM_HPP
