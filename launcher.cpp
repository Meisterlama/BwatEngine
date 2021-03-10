#define BMATH_IMPLEMENTATION
#include "Math/Math.hpp"

#define ENTITY_IMPLEMENTATION
#include "ECS/Entity.hpp"

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
	
	editor.DestroyImGui();

	engine.Close();

	return 0;
}
