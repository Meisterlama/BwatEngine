#include "Scripts/ScriptTest.hpp"
#include "Time.hpp"
#include "Debug/Logger.hpp"

void ScriptTest::Start()
{

}

void ScriptTest::Update()
{
	timer -= BwatEngine::Time::deltaTime;

	if (timer < 0.f)
	{
		LogInfo("Bonjour ce script marche");
		timer = initTImer;
	}
}