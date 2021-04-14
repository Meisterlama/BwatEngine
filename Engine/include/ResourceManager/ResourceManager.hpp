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

        static ResourceManager* Instance();

        /* ************************************************************************* */

        /* constructors */
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager operator=(const ResourceManager) = delete;

        /* ************************************************************************* */

        /* All the load resources to call and stock on the good map */

        Rendering::Model* LoadModel(std::string path);

        Rendering::Texture* LoadTexture(std::string path, Rendering::Texture::Type type);

        /* ************************************************************************* */

        /* get the resources with the type */

        Rendering::Model* GetOrLoadModel(std::string path);

        Rendering::Texture* GetOrLoadTexture(std::string path, Rendering::Texture::Type type);

        /* ************************************************************************* */

        std::vector<std::string>& GetModelList();

        std::vector<std::string>& GetTextList();

    private:

        ResourceManager() = default;
        static ResourceManager* instance;

        bool dirtyModels = false;
        bool dirtyTextures = false;

        /* all the maps that stores the resources */
        // add the rig for skinning animation
        // add materials
        //std::unordered_map<std::string, SoundResource> sounds;
        std::unordered_map<std::string, std::unique_ptr<Rendering::Model>> models;
        std::unordered_map<std::string, std::unique_ptr<Rendering::Texture>> textures;

        /* ************************************************************************* */
        std::vector<std::string> modelsKey;
        void UpdateModelsKey();
        std::vector<std::string> texturesKey;
        void UpdateTexturesKey();

        Rendering::Texture* GetTexture(std::string path);
        Rendering::Model* GetModel(std::string path);


    };
}
#endif