#ifndef ENGINE_ECS_COMPONENTS_RENDERABLE_HPP
#define ENGINE_ECS_COMPONENTS_RENDERABLE_HPP

#include "Math/Vector/Vector3.hpp"
#include "Rendering/Model.hpp"

namespace BwatEngine
{
    struct RenderableComponent
    {
        RenderableComponent() = default;
        RenderableComponent(Rendering::Model* model)
            : model(model)
            , materials(model->GetDefaultMaterials())
        {
        }

        Rendering::Model* model = nullptr;
        std::vector<Rendering::Material*> materials;
        
    };
}

#endif //ENGINE_ECS_COMPONENTS_RENDERABLE_HPP