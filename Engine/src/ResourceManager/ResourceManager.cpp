#include "ResourceManager/ResourceManager.hpp"
#include <cstring>

ResourceManager::ResourceManager()
{
    instance = this;
}

template<typename T>
void ResourceManager::LoadResource(const char* path)
{

}
/*
template<>
void ResourceManager::LoadResource<SoundResource>(const char* path)
{

}
*/
template<>
void ResourceManager::LoadResource<Rendering::Model>(const char* path)
{
    if (!path)
        return;

    std::string str(path);
    Rendering::Model toLoad ( str );
    models.emplace(path, toLoad);
};

template<>
void ResourceManager::LoadResource<Rendering::Texture>(const char* path)
{
    if (!path)
        return;

    Rendering::Texture toLoad;
    toLoad.TextureFromFile(path);
    textures.emplace(path, toLoad);
};

template<typename T>
T* ResourceManager::GetResource(const char* path) {}

/*
template<>
SoundResource* ResourceManager::GetResource<SoundResource>(const char* path)
{
    if (sounds.find(path) != sounds.cend())
        return sounds[path];

    return nullptr;
}
*/

template<>
Rendering::Model* ResourceManager::GetResource<Rendering::Model>(const char* path)
{
    if (models.find(path) != models.cend())
        return &models[path];

    return nullptr;
}

template<>
Rendering::Texture* ResourceManager::GetResource<Rendering::Texture>(const char* path)
{
    if (textures.find(path) != textures.cend())
        return &textures[path];

    return nullptr;
}