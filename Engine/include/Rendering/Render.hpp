#ifndef BWATENGINE_RENDER_HPP
#define BWATENGINE_RENDER_HPP

#include <string>
#include "Window.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "camera.hpp"
#include "light.hpp"

namespace Rendering
{
    class Render
    {
    public:
        Render();

        void RenderScene();

        Bwat::Window mainWindow;
        Camera cam;
        Shader myShaderLight;
        Model* myModel;

        std::vector<Light*> lights;

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
    };
}


#endif //BWATENGINE_RENDER_HPP
