#include "Rendering/camera.hpp"
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace Rendering;

Camera::Camera()
{

}

Camera::~Camera()
{

}


void Camera::UseFreeFly(Bwat::Window* win,float deltaTime)
{
    if (glfwGetKey(win->window, GLFW_KEY_F1))
        lockMouse = !lockMouse;

    if (lockMouse)
    {
        MouseMovement(win, deltaTime);
        CameraMovementFF(win, deltaTime);
    }
}

void Camera::MouseMovement(Bwat::Window* win, float deltaTime)
{
    glfwGetCursorPos(win->window, &xpos, &ypos);
    float xdelta_pos = xpos - win->GetWidth() / 2;
    float ydelta_pos = ypos - win->GetHeight() / 2;

    float sensitivity_mouse = 0.1f;

    xdelta_pos *= sensitivity_mouse * deltaTime;
    ydelta_pos *= sensitivity_mouse * deltaTime;

    yaw -= xdelta_pos;
    pitch -= ydelta_pos;

    if (pitch >= BMath::PI / 2)
        pitch = BMath::PI / 2;

    else if (pitch <= -BMath::PI / 2)
        pitch = -BMath::PI / 2;


    glfwSetCursorPos(win->window, win->GetWidth() / 2, win->GetHeight() / 2);
}

void Camera::CameraMovementFF(Bwat::Window* win, float deltaTime)
{

    float Speed = 4.f;
    float FrameSpeed = Speed * deltaTime;


    if (glfwGetKey(win->window, GLFW_KEY_LEFT_SHIFT))
        FrameSpeed *= 3.f;


    float ForwardVelocity = 0.f;
    if (glfwGetKey(win->window, GLFW_KEY_W))
        ForwardVelocity = -FrameSpeed;
    if (glfwGetKey(win->window, GLFW_KEY_S))
        ForwardVelocity = FrameSpeed;


    float StrafeVelocity = 0.f;
    if (glfwGetKey(win->window, GLFW_KEY_A))
        StrafeVelocity = -FrameSpeed;
    if (glfwGetKey(win->window, GLFW_KEY_D))
        StrafeVelocity = FrameSpeed;

    if (glfwGetKey(win->window, GLFW_KEY_SPACE))
        cameraPos.Y += Speed * deltaTime;

    if (glfwGetKey(win->window, GLFW_KEY_LEFT_CONTROL))
        cameraPos.Y -= Speed * deltaTime;

    cameraPos.Z += cos(-yaw) * cos(pitch) * ForwardVelocity;
    cameraPos.X += sin(yaw) * cos(-pitch) * ForwardVelocity;
    cameraPos.Y -= sin(pitch) * ForwardVelocity;

    cameraPos.Z += sin(-yaw) * StrafeVelocity;
    cameraPos.X += cos(-yaw) * StrafeVelocity;

    glfwSetInputMode(win->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

BMath::Matrix4<float> Camera::GetViewMatrix()
{
    BMath::Matrix4<float> View{1};
    View *= BMath::Matrix4<float>::CreateTranslationMat(-cameraPos);
    View *= BMath::Matrix4<float>::CreateYRotationMat(yaw);
    View *= BMath::Matrix4<float>::CreateXRotationMat(pitch);
    return View;
}

