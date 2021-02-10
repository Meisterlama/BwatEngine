#include "Rendering/light.hpp"
#include <iostream>

using namespace Rendering;

Light::Light() : 
ambient(0),diffuse(0),specular(0)
{
}

/*
Light::Light(Vec3 pos, Core::Maths::Vec3 ambi, Core::Maths::Vec3 diffu, Core::Maths::Vec3 spec) : position(pos),
ambient(ambi), diffuse(diffu), specular(spec)
{
    
}

Light::Light(Core::Maths::Vec3 pos, Core::Maths::Vec3 ambi, Core::Maths::Vec3 diffu, Core::Maths::Vec3 spec, int type) : position(pos),
ambient(ambi), diffuse(diffu), specular(spec) ,typeoflight(type)
{
    
}

void Light::apply_value_shader(Shader* shader , const std::string& i) const
{
    shader->use();

    shader->setVec3("lights[" + i + "].ambient", ambient.x, ambient.y, ambient.z);
    shader->setVec3("lights[" + i + "].diffuse", diffuse.x, diffuse.y, diffuse.z);
    shader->setVec3("lights[" + i + "].specular", specular.x, specular.y, specular.z);

    shader->setFloat("material.shininess", matShininess);
    shader->setInt("material.diffuse", matDiffuse);
    shader->setInt("material.specular", matSpecular);

    shader->setFloat("lights[" + i + "].constant",  constant);
    shader->setFloat("lights[" + i + "].linear",    linear);
    shader->setFloat("lights[" + i + "].quadratic", quadratic);

    shader->setFloat("lights[" + i + "].cutOff", cutoff);
    shader->setFloat("lights[" + i + "].outerCutOff", outerCutoff);

    shader->setVec3("lights[" + i + "].position", position.x, position.y, position.z);
    shader->setVec3("lights[" + i + "].direction", direction.x, direction.y, direction.z);
    shader->setInt("lights[" + i + "].typeoflight", typeoflight);
}

void Light::set_value_material(int diffu, int spec, float shine)
{
    matDiffuse = diffu;
    matSpecular = spec;
    matShininess = shine;

}

void Light::value_of_attenuation(float cons, float line, float quad)
{
    constant = cons;
    linear = line;
    quadratic = quad;
}

void Light::position_and_direction(Core::Maths::Vec3 pos,Core::Maths::Vec3 dir)
{
    position = pos;
    direction =dir;
}

void Light::value_of_spotlight(float cut, float outer)
{
    cutoff = cos(cut * M_PI / 180) ;
    outerCutoff = cos(outer * M_PI / 180);
}

void Light::set_nbr_of_light(int nbr)
{
    nbrlights = nbr;
}*/
