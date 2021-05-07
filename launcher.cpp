#define BMATH_IMPLEMENTATION
#include "Math/Math.hpp"



#include "Engine.hpp"

#if BWATEDITOR
#include "EditorInterface.hpp"
#endif

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

#if defined(BWATEDITOR)
	EditorInterface editor(&engine);
	editor.Initialise();
#endif

	while (engine.ShouldRun())
	{
		engine.Update();

#if defined(BWATEDITOR)
		editor.OnTick();
#endif

    }
#if defined(BWATEDITOR)
	editor.Close();
#endif

    engine.Close();

	return 0;
}
