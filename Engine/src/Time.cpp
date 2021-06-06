#include <GLFW/glfw3.h>
#include "Time.hpp"

void BwatEngine::Time::Update()
{
    double currentFrame = glfwGetTime();
    Time::deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
void BwatEngine::Time::Reset()
{
    Time::deltaTime = 0.0f;
    Time::lastFrame = glfwGetTime();
}

double BwatEngine::Time::deltaTime = 0.0f;
double BwatEngine::Time::lastFrame = 0.0f;