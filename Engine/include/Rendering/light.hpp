#pragma once

#include "Math/Math.hpp"
#include "shader.hpp"

namespace Rendering
{

    class Light
    {
    private:

    public:
        BMath::vec3f position{ 0,0,0 };
        BMath::vec3f direction{ 0,0,0 };

        // classic
        BMath::vec3f ambient{ 0,0,0 };
        BMath::vec3f diffuse{ 0,0,0 };
        BMath::vec3f specular{ 0,0,0 };


        Light();
        ~Light();

        //Methods

    };

}