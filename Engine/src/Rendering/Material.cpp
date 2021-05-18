#include "Rendering/Material.hpp"
#include <assimp/material.h>
#include "ResourceManager/ResourceManager.hpp"

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

    glActiveTexture(GL_TEXTURE0);
}

void Material::SetDiffuse(Texture& texture)
{
    diffuse = &texture;
}