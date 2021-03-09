#define BMATH_IMPLEMENTATION
#include "Math/Math.hpp"

#define ENTITY_IMPLEMENTATION
#include "ECS/Entity.hpp"

#include "Engine.hpp"

int main()
{
   
    using namespace BwatEngine;

	Engine engine;
	engine.Update();
	engine.Close();

	return 0;
}
