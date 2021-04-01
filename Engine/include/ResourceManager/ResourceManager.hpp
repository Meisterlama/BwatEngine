#ifndef RESOURCEMANAGER_RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_RESOURCEMANAGER_HPP_

#include <string>
#include <vector>
#include <unordered_map>
#include "Rendering/Model.hpp"

namespace BwatEngine
{

    class ResourceManager
    {
    public:



        /* the instance for the singleton */

        static ResourceManager* Instance()
        {
            static ResourceManager* instance = nullptr;
            if (instance == nullptr)
                instance = new ResourceManager;

            return instance;
        }

        /* ************************************************************************* */

        /* constructors */
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager operator=(const ResourceManager) = delete;

        /* ************************************************************************* */

        /* All the load resources with template to call and stock on the good map */

        //template<>
        //void LoadResource<SoundResource>(const std::string& path);
        Rendering::Model* LoadModel(std::string path)
        {
            auto it = models.emplace(path, std::make_unique<Rendering::Model>(path));
            return it.first->second.get();
        }

        Rendering::Texture* LoadTexture(std::string path, Rendering::Texture::Type type)
        {
            auto it = textures.emplace(path, std::make_unique<Rendering::Texture>(path, type));
            return it.first->second.get();
        }

        /* ************************************************************************* */

        /* get the resources with the template type */

        /*template<>
        //T* GetResource<SoundResource>(const char* path)
        {
            if (sounds.find(path) != sounds.cend())
                return sounds[path];

            return nullptr;
        }
        */

        Rendering::Model* GetModel(std::string path)
        {
            auto it = models.find(path);
            if (it != models.cend())
                return it->second.get();

            return nullptr;
        }

        Rendering::Model* GetOrLoadModel(std::string path)
        {
            Rendering::Model* res = ResourceManager::Instance()->GetModel(path);
            return (res != nullptr) ? res : LoadModel(path);
        }

        Rendering::Texture* GetTexture(std::string path)
        {
            auto it = textures.find(path);
            if (it != textures.cend())
                return it->second.get();

            return nullptr;
        }

        Rendering::Texture* GetOrLoadTexture(std::string path, Rendering::Texture::Type type)
        {
            Rendering::Texture* res = ResourceManager::Instance()->GetTexture(path);
            return (res != nullptr) ? res : LoadTexture(path, type);
        }

        /* ************************************************************************* */
        std::vector<Rendering::Model*> GetModelList()
        {
            std::vector<Rendering::Model*> modelList;
            for (auto &it : models)
            {
                modelList.push_back(it.second.get());
            }
            return modelList;
        }

        std::vector<Rendering::Texture*> GetTextList()
        {
            std::vector<Rendering::Texture*> textList;
            for (auto &it : textures)
            {
                textList.push_back(it.second.get());
            }
            return textList;
        }

    private:

        ResourceManager() = default;
        static ResourceManager* instance;

        /* all the maps that stores the resources */
        // add the rig for skinning animation
        // add materials
        //std::unordered_map<std::string, SoundResource> sounds;
        std::unordered_map<std::string, std::unique_ptr<Rendering::Model>> models;
        std::unordered_map<std::string, std::unique_ptr<Rendering::Texture>> textures;

        /* ************************************************************************* */

    };
}
#endif