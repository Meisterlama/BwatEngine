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


void Camera::usefreefly(Bwat::Window* win,float deltaTime)
{
    if (glfwGetKey(win->window, GLFW_KEY_L))
        lockMouse = !lockMouse;

    if (lockMouse)
    {
        // ===================================== Mouse ===================================== // 

        glfwGetCursorPos(win->window, &xpos, &ypos);
        float xdelta_pos = xpos - win->GetWidth() / 2;
        float ydelta_pos = ypos - win->GetHeight() / 2;

        float sensitivity_mouse = 0.1f;

        xdelta_pos *= sensitivity_mouse * deltaTime;
        ydelta_pos *= sensitivity_mouse * deltaTime;

        yaw -= xdelta_pos;
        pitch += -ydelta_pos;

        if (pitch >= BMath::PI / 2)
            pitch = BMath::PI / 2;

        else if (pitch <= -BMath::PI / 2)
            pitch = -BMath::PI / 2;


        glfwSetCursorPos(win->window, win->GetWidth() / 2, win->GetHeight() / 2);

        // ===================================== Movement ===================================== // 

        float Speed = 4.f;
        float FrameSpeed = Speed * deltaTime;


        if (glfwGetKey(win->window, GLFW_KEY_Q))
        {
            FrameSpeed *= 3.f;
        }

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

        if (glfwGetKey(win->window, GLFW_KEY_Z))
            cameraPos.Y -= Speed * deltaTime;

        cameraPos.Z += cos(-yaw) * cos(pitch) * ForwardVelocity;
        cameraPos.X += sin(yaw) * cos(-pitch) * ForwardVelocity;
        cameraPos.Y -= sin(pitch) * ForwardVelocity;

        cameraPos.Z += sin(-yaw) * StrafeVelocity;
        cameraPos.X += cos(-yaw) * StrafeVelocity;

        //std::cout << cameraPos.X << " | y : " << cameraPos.Y << "  | z  :" << cameraPos.Z << std::endl;

        glfwSetInputMode(win->window,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);

    }
}


BMath::Matrix4<float> Camera::ViewOfCamera()
{
    BMath::Matrix4<float> View{1};
    
    //View = View * BMath::Matrix4<float>::CreateTranslationMat(-cameraPos).Transpose();
    //View = View * BMath::Matrix4<float>::CreateYRotationMat(yaw);
    //View = View * BMath::Matrix4<float>::CreateXRotationMat(-pitch);
    View = BMath::Matrix4<float>::CreateTRSMat(-cameraPos, {pitch,yaw,0 }, { 1,1,1 });

    return View;
}

