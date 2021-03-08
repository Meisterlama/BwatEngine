#ifndef ENGINE_ECS_COMPONENTS_RENDERABLE_HPP
#define ENGINE_ECS_COMPONENTS_RENDERABLE_HPP

#include "Math/Vector/Vector3.hpp"
#include "Rendering/Model.hpp"

namespace BwatEngine
{
    struct RenderableComponent
    {
        Rendering::Model* model;
    };
}

#endif //ENGINE_ECS_COMPONENTS_RENDERABLE_HPP