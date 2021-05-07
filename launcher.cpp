#define BMATH_IMPLEMENTATION
#include "Math/Math.hpp"



#include "Engine.hpp"
#include "EditorInterface.hpp"
#include "Debug/Logger.hpp"

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

    FILE* myFile;
    myFile = fopen("log.txt", "w");

    if (myFile == nullptr)
    {
        std::cout << "error file";
    }
    else
    {
        BLogger::LogAddFp(myFile, 0);
    }

	Engine engine;


	EditorInterface editor(&engine);
	editor.Initialise();

	while (engine.ShouldRun())
	{
		engine.Update();
		editor.OnTick();
	}

	engine.Close();

	fclose(myFile);
	return 0;
}
