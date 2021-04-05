#include "Rendering/Light.hpp"

using namespace Rendering;

// it's empty, use "= default"
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

		// you can only use one light ?
    shader->setVec3("light.ambient", ambient.X, ambient.Y, ambient.Z);
    shader->setVec3("light.diffuse", diffuse.X, diffuse.Y, diffuse.Z);
    shader->setVec3("light.specular", specular.X, specular.Y, specular.Z);

    //shader->setFloat("light.constant",  constant);
    //shader->setFloat("light.linear",    linear);
    //shader->setFloat("light.quadratic", quadratic);

    //shader->setFloat("light.cutOff", cutoff);
    //shader->setFloat("light.outerCutOff", outerCutoff);

    shader->setVec3("light.position", position.X, position.Y, position.Z);/*
    shader->setVec3("light.direction", direction.X, direction.Y, direction.Z);*//*
    shader->setInt("light.typeoflight", typeoflight);*/
}

