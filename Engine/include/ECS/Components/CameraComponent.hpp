#ifndef ENGINE_ECS_COMPONENTS_CAMERA_HPP
#define ENGINE_ECS_COMPONENTS_CAMERA_HPP

#include "Math/Matrix/Matrix4.hpp"

namespace BwatEngine
{
    struct CameraComponent
    {
        bool isOrtho = false;
        float near = 0.1;
        float far = 1000.f;
        float left = 600.0f;
        float right = -600.0f;
        float top = 360.0f;
        float bottom = 360.0f;
        float aspect = 16.0f / 9.0f;
        float fov = 80.0f;

        Math::Mat4f GetProjectionMatrix()
        {
            return (isOrtho) ? Math::Mat4f::CreateOrtho(left, right, bottom, top, near, far)
                             : Math::Mat4f::CreatePerspective(fov, aspect, near, far);
        }
    };
}

#endif //ENGINE_ECS_COMPONENTS_CAMERA_HPP