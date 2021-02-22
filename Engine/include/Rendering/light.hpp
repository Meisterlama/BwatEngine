#pragma once

#include "Math/Math.hpp"
#include "shader.hpp"

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
        BMath::vec3f position{ 0,0,0 };
        BMath::vec3f direction{ 0,0,0 };

        // classic
        BMath::vec3f ambient{ 0,0,0 };
        BMath::vec3f diffuse{ 0,0,0 };
        BMath::vec3f specular{ 0,0,0 };

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

        Light(TYPE_LIGHT myType, BMath::vec3f tmpAmbient, BMath::vec3f tmpDiffuse, BMath::vec3f tmpSpecular);

        //Methods
        void SetAmbient(BMath::vec3f tmpAmbient);
        void SetDiffuse(BMath::vec3f tmpDiffuse);
        void SetSpecular(BMath::vec3f tmpSpecular);

        void SetAttenuation(float tmpConstant, float tmpLinear, float tmpQuadratic);
        void SetMaterialLight(int tmpMatDiffuse, int tmpMatSpecular, float tmpMatShininess);
        void SetSpotLightValues(float tmpCutOff, float tmpOuterCutOff);

        void ApplyOnShader(Shader* shader, const std::string& i) const;

    };

}