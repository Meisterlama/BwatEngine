#include "Rendering/Camera.hpp"
#include "Inputs/InputHandler.hpp"

using namespace Rendering;

Camera::Camera()
{

}

Camera::~Camera()
{

}


void Camera::UseFreeFly(Bwat::Window* win,float deltaTime)
{
    if (BwatEngine::InputHandler::GetKeyboardDown(BwatEngine::KEY_F1))
    {
        lockMouse = !lockMouse;
        glfwSetInputMode(win->window, GLFW_CURSOR, (lockMouse) ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }
    if (lockMouse)
    {
        MouseMovement(win, deltaTime);
        CameraMovementFF(win, deltaTime);
    }
}

void Camera::MouseMovement(Bwat::Window* win, float deltaTime)
{
    BwatEngine::Math::Vec2f mouseDelta = BwatEngine::InputHandler::GetMouseDelta();

    float sensitivity_mouse = 0.1f;

    mouseDelta *= sensitivity_mouse * deltaTime;

    yaw -= mouseDelta.X;
    pitch -= mouseDelta.Y;

    if (pitch >= BwatEngine::Math::PI / 2)
        pitch = BwatEngine::Math::PI / 2;

    else if (pitch <= -BwatEngine::Math::PI / 2)
        pitch = -BwatEngine::Math::PI / 2;
}

void Camera::CameraMovementFF(Bwat::Window* win, float deltaTime)
{

    float Speed = 4.f;
    float FrameSpeed = Speed * deltaTime;


    if (BwatEngine::InputHandler::GetKeyboard(BwatEngine::KEY_LEFT_SHIFT))
        FrameSpeed *= 3.f;


    float ForwardVelocity = 0.f;
    if (BwatEngine::InputHandler::GetKeyboard(BwatEngine::KEY_W))
        ForwardVelocity = -FrameSpeed;
    if (BwatEngine::InputHandler::GetKeyboard(BwatEngine::KEY_S))
        ForwardVelocity = FrameSpeed;


    float StrafeVelocity = 0.f;
    if (BwatEngine::InputHandler::GetKeyboard(BwatEngine::KEY_A))
        StrafeVelocity = -FrameSpeed;
    if (BwatEngine::InputHandler::GetKeyboard(BwatEngine::KEY_D))
        StrafeVelocity = FrameSpeed;

    if (BwatEngine::InputHandler::GetKeyboard(BwatEngine::KEY_SPACE))
        cameraPos.Y += Speed * deltaTime;

    if (BwatEngine::InputHandler::GetKeyboard(BwatEngine::KEY_LEFT_CONTROL))
        cameraPos.Y -= Speed * deltaTime;

    cameraPos.Z += cos(-yaw) * cos(pitch) * ForwardVelocity;
    cameraPos.X += sin(yaw) * cos(-pitch) * ForwardVelocity;
    cameraPos.Y -= sin(pitch) * ForwardVelocity;

    cameraPos.Z += sin(-yaw) * StrafeVelocity;
    cameraPos.X += cos(-yaw) * StrafeVelocity;

}

BwatEngine::Math::Mat4f Camera::GetViewMatrix()
{
    BwatEngine::Math::Mat4f View{1};
    View *= BwatEngine::Math::Mat4f::CreateTranslationMat(-cameraPos);
    View *= BwatEngine::Math::Mat4f::CreateYRotationMat(yaw);
    View *= BwatEngine::Math::Mat4f::CreateXRotationMat(pitch);
    return View;
}

