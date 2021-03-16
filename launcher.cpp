#define BMATH_IMPLEMENTATION
#include "Math/Math.hpp"

#include "Engine.hpp"
#include "EditorInterface.hpp"

int main()
{
    using namespace BwatEngine;

	Engine engine;

	EditorInterface editor(&engine);
	editor.Initialise(engine.context.window);

	while (engine.ShouldRun())
	{
		engine.Update();
		editor.OnTick();
	}
	
	engine.Close();

	return 0;
}
