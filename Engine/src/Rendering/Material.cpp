#include "Rendering/Material.hpp"
#include <assimp/material.h>
#include "ResourceManager/ResourceManager.hpp"
#include "Rendering/Shader.hpp"

using namespace Rendering;

Material::Material(const char* basePath, const aiMaterial& from)
{
    std::string basePathStr = basePath;
    {
        aiString path;
        if (from.GetTexture(aiTextureType_NORMALS, 0, &path) == aiReturn_SUCCESS)
            normal = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture(basePathStr + path.C_Str());
    }

    {
        aiString path;
        if (from.GetTexture(aiTextureType_DIFFUSE, 0, &path) == aiReturn_SUCCESS)
            albedoMap = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture(basePathStr + path.C_Str());
    }

    {
        aiString path;
        if (from.GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &path) == aiReturn_SUCCESS)
            aoMap = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture(basePathStr + path.C_Str());
    }

    {
        aiString path;
        if (from.GetTexture(aiTextureType_METALNESS, 0, &path) == aiReturn_SUCCESS)
            metallicMap = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture(basePathStr + path.C_Str());
    }

    {
        aiString path;
        if (from.GetTexture(aiTextureType_DIFFUSE_ROUGHNESS, 0, &path) == aiReturn_SUCCESS)
            roughnessMap = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture(basePathStr + path.C_Str());
    }
 
}

void Material::Bind()
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

    shader.SetBool("isTilling", isTilling);
    shader.SetVec2("tile", tile.X, tile.Y);

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
