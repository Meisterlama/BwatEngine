#pragma once

#include "Math/Math.hpp"
#include "shader.hpp"

namespace Rendering
{

    class Light
    {
    private:

    public:
        Math::vec3f position{ 0,0,0 };
        Math::vec3f direction{ 0,0,0 };

        // classic
        Math::vec3f ambient{ 0,0,0 };
        Math::vec3f diffuse{ 0,0,0 };
        Math::vec3f specular{ 0,0,0 };


        Light();
        ~Light();

        //Methods

    };

}