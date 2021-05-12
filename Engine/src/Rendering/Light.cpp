#include "Rendering/Light.hpp"

using namespace Rendering;

Light::Light() 
{
}


void Light::ApplyOnShader(Shader* shader , const std::string& i) const
{
    shader->Use();

    shader->SetVec3("light["+ i +"].position", position.X, position.Y, position.Z);
    shader->SetVec3("light[" + i + "].direction", direction.X, direction.Y, direction.Z);
    shader->SetInt("light[" + i + "].typeoflight", typeoflight);

    shader->SetVec3("light[" + i + "].ambient", ambient.X, ambient.Y, ambient.Z);
    shader->SetVec3("light[" + i + "].diffuse", diffuse.X, diffuse.Y, diffuse.Z);
    shader->SetVec3("light[" + i + "].specular", specular.X, specular.Y, specular.Z);

    if (typeoflight == TYPE_LIGHT::Point || typeoflight == TYPE_LIGHT::Spot)
    {
        shader->SetFloat("light[" + i + "].constant", constant);
        shader->SetFloat("light[" + i + "].linear", linear);
        shader->SetFloat("light[" + i + "].quadratic", quadratic);

        if (typeoflight == TYPE_LIGHT::Spot)
        {
            shader->SetFloat("light[" + i + "].cutOff", BwatEngine::Math::Cos(cutoff));
            shader->SetFloat("light[" + i + "].outerCutOff", BwatEngine::Math::Cos(outerCutoff));
        }
    }

}

