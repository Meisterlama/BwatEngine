#pragma once

#include "Math/Math.hpp"
#include "Shader.hpp"

namespace Rendering
{
    enum TYPE_LIGHT
    {
        Directional,
        Point,
        Spot
    };

    class Light
    {
    private:

    public:
        BwatEngine::Math::Vec3f position{ 0,0,0 };
        BwatEngine::Math::Vec3f direction{ 0,0,0 };

        // classic
        BwatEngine::Math::Vec3f ambient{ 0,0,0 };
        BwatEngine::Math::Vec3f diffuse{ 0,0,0 };
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

        Light(TYPE_LIGHT myType, BwatEngine::Math::Vec3f tmpAmbient, BwatEngine::Math::Vec3f tmpDiffuse, BwatEngine::Math::Vec3f tmpSpecular);

        //Methods
        void SetAmbient(BwatEngine::Math::Vec3f tmpAmbient);
        void SetDiffuse(BwatEngine::Math::Vec3f tmpDiffuse);
        void SetSpecular(BwatEngine::Math::Vec3f tmpSpecular);

        void SetAttenuation(float tmpConstant, float tmpLinear, float tmpQuadratic);
        void SetMaterialLight(int tmpMatDiffuse, int tmpMatSpecular, float tmpMatShininess);
        void SetSpotLightValues(float tmpCutOff, float tmpOuterCutOff);

        void ApplyOnShader(Shader* shader, const std::string& i) const;

    };

}