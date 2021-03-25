#include "Rendering/Material.hpp"
#include <assimp/material.h>

using namespace Rendering;

Material::Material(const aiMaterial& from)
{
    {
        aiString path;
        if (from.GetTexture(aiTextureType_DIFFUSE, 0, &path) == aiReturn_SUCCESS)
            diffuse = new Texture(path.C_Str()); // TODO: use resrc manager 
            
    }
    {
        aiString path;
        if (from.GetTexture(aiTextureType_SPECULAR, 0, &path) == aiReturn_SUCCESS)
            specular = new Texture(path.C_Str());
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