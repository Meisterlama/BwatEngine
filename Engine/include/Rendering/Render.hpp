#ifndef BWATENGINE_RENDER_HPP
#define BWATENGINE_RENDER_HPP

#include <string>
#include "../../Engine/include/Window.hpp"
#include "Rendering/shader.hpp"
#include "Rendering/model.hpp"
#include "Rendering/camera.hpp"
#include "Rendering/light.hpp"

namespace Rendering
{
    class Render
    {
    public:
        Render();

        void RenderScene(Bwat::Window mainWindow, float deltaTime);

        Camera cam;
        Shader myShaderLight;
        Model* myModel;

        std::vector<Light*> lights;
    };
}


#endif //BWATENGINE_RENDER_HPP
