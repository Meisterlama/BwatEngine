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
    if (normal)
        normal->Use();

    glActiveTexture(GL_TEXTURE1);
    if (albedoMap)
        albedoMap->Use();
    
    glActiveTexture(GL_TEXTURE2);
    if (metallicMap)
        metallicMap->Use();
    
    glActiveTexture(GL_TEXTURE3);
    if (roughnessMap)
        roughnessMap->Use();
    
    glActiveTexture(GL_TEXTURE4);
    if (aoMap)
        aoMap->Use();

    
    glActiveTexture(GL_TEXTURE0);


}


void Material::ApplyToShader(Shader& shader)
{
    shader.SetBool("material.isTextured", isTextured);

    shader.SetBool("material.isColor", isColor);
    shader.SetVec4("material.color", color.X, color.Y, color.Z, color.W);

    shader.SetFloat("material.shininess", shininess);

    shader.SetInt("material.normal", 0);
    shader.SetInt("material.albedoMap", 1);
    shader.SetInt("material.metallicMap", 2);
    shader.SetInt("material.roughnessMap", 3);
    shader.SetInt("material.aoMap", 4);

    shader.SetInt("material.isNormal", (int)(normal != nullptr) );

    if (!isTextured)
    {
        shader.SetVec3("material.albedo",albedo.X,albedo.Y,albedo.Z);
        shader.SetFloat("material.metallic", metallic);
        shader.SetFloat("material.roughness",roughness);
        shader.SetFloat("material.ao",ao);
    }
}
