#include "Rendering/light.hpp"

using namespace Rendering;

Light::Light() : 
ambient(0),diffuse(0),specular(0)
{
}


Light::Light(TYPE_LIGHT myType, BwatEngine::Math::Vec3f tmpAmbient, BwatEngine::Math::Vec3f tmpDiffuse, BwatEngine::Math::Vec3f tmpSpecular)
{
    typeoflight = myType;
    ambient = tmpAmbient;
    diffuse = tmpDiffuse;
    specular = tmpSpecular;
}

void Light::SetAmbient(BwatEngine::Math::Vec3f tmpAmbient)
{
    ambient = tmpAmbient;
}

void Light::SetDiffuse(BwatEngine::Math::Vec3f tmpDiffuse)
{
    diffuse = tmpDiffuse;
}

void Light::SetSpecular(BwatEngine::Math::Vec3f tmpSpecular)
{
    specular = tmpSpecular;
}

void Light::SetAttenuation(float tmpConstant, float tmpLinear, float tmpQuadratic)
{
    constant = tmpConstant;
    linear = tmpLinear;
    quadratic = tmpQuadratic;
}

void Light::SetMaterialLight(int tmpMatDiffuse, int tmpMatSpecular, float tmpMatShininess)
{
    matDiffuse = tmpMatDiffuse;
    matSpecular = tmpMatSpecular;
    matShininess = tmpMatShininess;
}

void Light::SetSpotLightValues(float tmpCutOff, float tmpOuterCutOff)
{
    cutoff = tmpCutOff;
    outerCutoff = tmpOuterCutOff;
}


void Light::ApplyOnShader(Shader* shader , const std::string& i) const
{
    shader->use();

    shader->setVec3("lights[" + i + "].ambient", ambient.X, ambient.Y, ambient.Z);
    shader->setVec3("lights[" + i + "].diffuse", diffuse.X, diffuse.Y, diffuse.Z);
    shader->setVec3("lights[" + i + "].specular", specular.X, specular.Y, specular.Z);

    shader->setFloat("material.shininess", matShininess);
    shader->setInt("material.diffuse", matDiffuse);
    shader->setInt("material.specular", matSpecular);

    shader->setFloat("lights[" + i + "].constant",  constant);
    shader->setFloat("lights[" + i + "].linear",    linear);
    shader->setFloat("lights[" + i + "].quadratic", quadratic);

    shader->setFloat("lights[" + i + "].cutOff", cutoff);
    shader->setFloat("lights[" + i + "].outerCutOff", outerCutoff);

    shader->setVec3("lights[" + i + "].position", position.X, position.Y, position.Z);
    shader->setVec3("lights[" + i + "].direction", direction.X, direction.Y, direction.Z);
    shader->setInt("lights[" + i + "].typeoflight", typeoflight);
}

