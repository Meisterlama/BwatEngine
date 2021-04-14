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
        //aiColor3D diffuseColor;
        //from.Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
        //color = { diffuseColor.r, diffuseColor.g, diffuseColor.b };
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
}

void Material::SetDiffuse(Texture& texture)
{
    diffuse = &texture;
}