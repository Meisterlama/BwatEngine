#include "Rendering/Light.hpp"

using namespace Rendering;

Light::Light() 
{
}


void Light::ApplyOnShader(Shader* shader , const std::string& i) const
{
    shader->use();

    shader->setVec3("light["+ i +"].position", position.X, position.Y, position.Z);
    shader->setVec3("light[" + i + "].direction", direction.X, direction.Y, direction.Z);
    shader->setInt("light[" + i + "].typeoflight", typeoflight);

    shader->setVec3("light[" + i + "].ambient", ambient.X, ambient.Y, ambient.Z);
    shader->setVec3("light[" + i + "].diffuse", diffuse.X, diffuse.Y, diffuse.Z);
    shader->setVec3("light[" + i + "].specular", specular.X, specular.Y, specular.Z);

    if (typeoflight == TYPE_LIGHT::Point || typeoflight == TYPE_LIGHT::Spot)
    {
        shader->setFloat("light[" + i + "].constant", constant);
        shader->setFloat("light[" + i + "].linear", linear);
        shader->setFloat("light[" + i + "].quadratic", quadratic);

        if (typeoflight == TYPE_LIGHT::Spot)
        {
            shader->setFloat("light[" + i + "].cutOff", BwatEngine::Math::Cos(cutoff));
            shader->setFloat("light[" + i + "].outerCutOff", BwatEngine::Math::Cos(outerCutoff));
        }
    }

}

