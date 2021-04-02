#ifndef ENGINE_ECS_COMPONENTS_CAMERA_HPP
#define ENGINE_ECS_COMPONENTS_CAMERA_HPP

#include "Math/Matrix/Matrix4.hpp."

namespace BwatEngine
{
    struct CameraComponent
    {
        Math::Mat4f projectionMat;
    };
}

#endif //ENGINE_ECS_COMPONENTS_CAMERA_HPP