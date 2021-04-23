#pragma once

#include "Math/Math.hpp"
#include "Shader.hpp"

namespace Rendering
{
    enum TYPE_LIGHT
    {
        Directional,
        Point,
        Spot,
        Size
    };

    struct Light
    {
        BwatEngine::Math::Vec3f position{ 0,0,0 };
        BwatEngine::Math::Vec3f direction{ 0,-1,0 };

        // classic
        BwatEngine::Math::Vec3f ambient{ 0,0,0 };
        BwatEngine::Math::Vec3f diffuse{ 1,1,1 };
        BwatEngine::Math::Vec3f specular{ 0,0,0 };

        // attenuation
        float constant = 1.f;
        float linear = 1.f;
        float quadratic = 1.f;

        //material
        int matDiffuse = 0;
        int matSpecular = 1;
        float matShininess = 32.0f;

        //spotlight 
        float cutoff = 0.f;
        float outerCutoff = 0.f;

        //nbr light and type ;
        TYPE_LIGHT typeoflight = Directional;
        int nbrlights = 1;


        Light();
        ~Light() {};

        void ApplyOnShader(Shader* shader, const std::string& i) const;

    };
}