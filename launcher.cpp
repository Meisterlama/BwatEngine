#define BMATH_IMPLEMENTATION
#include "Math/Math.hpp"



#include "Engine.hpp"
#include "EditorInterface.hpp"

#if defined(_MSC_VER) || defined(__MINGW32__)
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

extern "C"
{
DLLEXPORT int NvOptimusEnablement = 1;
DLLEXPORT int AmdPowerXpressRequestHighPerformance = 1;
}

int main()
{
    using namespace BwatEngine;


	Engine engine;


	EditorInterface editor(&engine);
	editor.Initialise();

	while (engine.ShouldRun())
	{
		engine.Update();
		editor.OnTick();
	}

	editor.Close();
	engine.Close();

	return 0;
}
