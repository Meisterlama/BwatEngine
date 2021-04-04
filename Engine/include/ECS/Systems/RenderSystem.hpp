#ifndef ENGINE_ECS_SYSTEMS_RENDER_HPP
#define ENGINE_ECS_SYSTEMS_RENDER_HPP

#include "Math/Vector/Vector3.hpp"

#include "ECS/System.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/Model.hpp"
#include "Window.hpp"
#include "Scene.hpp"

// you don't need to include these files in your .hpp
// see PhysicsSystem comments
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"

namespace BwatEngine
{
		// you are coding in C or C++ ?
		// make it static
    extern Entity gCamera;

    class RenderSystem : public System
    {

        Rendering::Shader shader;
				
				// initialize your ptr to nullptr
				// look at ColliderComponent.hpp comments
        Window* window;
        Entity camera = -1;

    public:

        Math::Vec3f clearColor = { 0.5f, 0.5f, 0.5f };

        void Init();

        // first time I am seeing a paramater's name starting with '_'
				// be consistent with your nomenclature
				void SetCamera(Entity _camera);
        
				// There is already a member Window*
				// Why is there a Window parameter ?
				// WIP Btw should be "const Window&" ?
				void Update(Window& win);
        

    };
}

#endif //ENGINE_ECS_SYSTEMS_RENDER_HPP
