#pragma once

#include "Math/Math.hpp"
#include "Window.hpp"

namespace Rendering
{
    class Camera
    {
    public:

        float yaw = 0;
        float pitch = 0;
        BwatEngine::Math::Vec3f cameraPos{0,0,5};

        double xpos = 0, ypos = 0;
        bool lockMouse = false;

        // constructor
        Camera();
        ~Camera();

        //method
        void UseFreeFly(Bwat::Window*, float);
        void MouseMovement(Bwat::Window* win, float deltaTime);
        void CameraMovementFF(Bwat::Window* win, float deltaTime);
        BwatEngine::Math::Mat4f GetViewMatrix();

    };

}
