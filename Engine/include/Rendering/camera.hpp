#pragma once

#include "../Math/Math.hpp"
#include "Window.hpp"
#include <imgui_impl_glfw.h>

namespace Rendering
{
    class Camera
    {
    public:

        float yaw = 0;
        float pitch = Math::PI / 2;
        Math::vec3f cameraPos;
        Math::vec3f cameraRot;
        double xpos = 0, ypos = 0;

        // constructor
        Camera();
        ~Camera();

        //method
        void usefreefly(Bwat::Window*, float);
        //Mat4 view_of_camera(Camera cam);


    };

}
