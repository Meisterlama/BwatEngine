#pragma once

#include "../Math/vec3.h"
#include "../Math/mat4.h"

#include <imgui_impl_glfw.h>


class Camera
{
    public :
    
        float yaw = 0;
        float pitch = M_PI / 2;
        Vec3 cameraPos;
        Vec3 cameraRot;
        double xpos,ypos;

        // constructor
        Camera();
        ~Camera();

        //method
        void usefreefly(GLFWwindow*,float);
        Mat4 view_of_camera(Camera cam);


};
