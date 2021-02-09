#include "camera.hpp"
#include <math.h>
#include <iostream>


Camera::Camera()
{

}

Camera::~Camera()
{

}

/*
void Camera::usefreefly(GLFWwindow* win,float deltaTime)
{
    // ===================================== Mouse ===================================== // 

    glfwGetCursorPos(win, &xpos, &ypos);
    float xdelta_pos = xpos - win.width/2;
    float ydelta_pos = ypos - win.height/2 ;

    float sensitivity_mouse = 0.1f;

    xdelta_pos *= sensitivity_mouse * deltaTime;
    ydelta_pos *= sensitivity_mouse * deltaTime;

    yaw += xdelta_pos;
    pitch += -ydelta_pos;

    if (pitch >= M_PI_2)
        pitch = M_PI_2 ;

    else if (pitch <= -M_PI_2)
        pitch = -M_PI_2;
        
    glfwSetCursorPos(win.window,win.width/2,win.height/2);

    // ===================================== Movement ===================================== // 

    float Speed = 4.f;
    float FrameSpeed = (float)(Speed * deltaTime);


    if(glfwGetKey(win.window, GLFW_KEY_Q))
        FrameSpeed *= 3.f;

    float ForwardVelocity = 0.f;
    if(glfwGetKey(win.window, GLFW_KEY_W))
        ForwardVelocity = -FrameSpeed;
    if(glfwGetKey(win.window, GLFW_KEY_S))
        ForwardVelocity = FrameSpeed;


    float StrafeVelocity = 0.f;
    if(glfwGetKey(win.window, GLFW_KEY_A))
        StrafeVelocity = -FrameSpeed;
    if(glfwGetKey(win.window, GLFW_KEY_D))
        StrafeVelocity = FrameSpeed;

    
    cameraPos.z += cos(yaw) * cos(pitch) * ForwardVelocity;
    cameraPos.x += sin(-yaw) * cos(-pitch) * ForwardVelocity;
    cameraPos.y -= sin(pitch) * ForwardVelocity ;

    cameraPos.z += sin(yaw)  * StrafeVelocity;
    cameraPos.x += cos(yaw)  * StrafeVelocity;

    glfwSetInputMode(win.window,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);

        
}*/

Mat4 Camera::view_of_camera(Camera cam)
{
    Mat4 View;
    View.identity();
    
    View = View * Mat4::create_translation_matrix({-cam.cameraPos.x, -cam.cameraPos.y, -cam.cameraPos.z});
    View = View * Mat4::create_y_rotation_matrix(cam.yaw);
    View = View * Mat4::create_x_rotation_matrix(-cam.pitch);

    return View;
}

