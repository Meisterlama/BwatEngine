#include "Rendering/Material.hpp"
#include <assimp/material.h>
#include "ResourceManager/ResourceManager.hpp"
#include "Rendering/Shader.hpp"

using namespace Rendering;

Material::Material(const aiMaterial& from)
{
    {
        aiString path;
        if (from.GetTexture(aiTextureType_DIFFUSE, 0, &path) == aiReturn_SUCCESS)
            diffuse =  BwatEngine::ResourceManager::Instance()->GetOrLoadTexture(path.C_Str(), Rendering::Texture::Type::E_DIFFUSE);
            
    }
    {
        aiString path;
        if (from.GetTexture(aiTextureType_SPECULAR, 0, &path) == aiReturn_SUCCESS)
            specular = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture(path.C_Str(), Rendering::Texture::Type::E_SPECULAR);
    }
    {
        aiString path;
        if (from.GetTexture(aiTextureType_NORMALS, 0, &path) == aiReturn_SUCCESS)
            normal = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture(path.C_Str(), Rendering::Texture::Type::E_NORMAL);
    }
 
}

void Material::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    if(diffuse)
        diffuse->Use();

    glActiveTexture(GL_TEXTURE1);
    if (specular)
        specular->Use();

    glActiveTexture(GL_TEXTURE2);
    if (normal)
        normal->Use();

    if (isTextured)
    {
        glActiveTexture(GL_TEXTURE5);
        if (albedoMap)
            albedoMap->Use();

        glActiveTexture(GL_TEXTURE6);
        if (metallicMap)
            metallicMap->Use();

        glActiveTexture(GL_TEXTURE7);
        if (roughnessMap)
            roughnessMap->Use();

        glActiveTexture(GL_TEXTURE8);
        if (aoMap)
            aoMap->Use();

    }

    glActiveTexture(GL_TEXTURE0);


}


void Material::ApplyToShader(Shader& shader)
{
    shader.SetBool("material.isColor", isColor);
    shader.SetVec4("material.color", color.X, color.Y, color.Z, color.W);

    shader.SetFloat("material.shininess", shininess);

    if (specular != nullptr)
        shader.SetInt("material.specular", 1);

    if (normal != nullptr)
        shader.SetInt("material.isNormal", 1);
    else
        shader.SetInt("material.isNormal", 0);

    if (!isTextured)
    {
        shader.SetVec3("albedo",albedo.X,albedo.Y,albedo.Z);
        shader.SetFloat("metallic", metallic);
        shader.SetFloat("roughness",roughness);
        shader.SetFloat("ao",ao);
    }
}
