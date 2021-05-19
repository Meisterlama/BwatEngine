#ifndef RESOURCEMANAGER_RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_RESOURCEMANAGER_HPP_

#include <string>
#include <vector>
#include <unordered_map>
#include "Rendering/Model.hpp"
#include "Rendering/Texture.hpp"
#include "Audio/Sound.hpp"
#include "ECS/Components/ScriptComponent.hpp"


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

        Audio::AudioData* LoadAudio(std::string path);

        std::string* LoadScript(std::string path);


        /* ************************************************************************* */

        /* get the resources with the type */

        Rendering::Model* GetOrLoadModel(std::string path);

        Rendering::Texture* GetOrLoadTexture(std::string path, Rendering::Texture::Type type = Rendering::Texture::Type::E_DIFFUSE);

        Audio::AudioData* GetOrLoadAudio(std::string path);

        std::string* GetOrLoadScript(std::string path);

        /* ************************************************************************* */

        std::vector<std::string>& GetModelList();

        std::vector<std::string>& GetTextList();

        std::vector<std::string>& getAudioList();

        std::vector<std::string>& getScriptList();

    private:

        ResourceManager() = default;
        static ResourceManager* instance;

        bool dirtyModels = false;
        bool dirtyTextures = false;
        bool dirtyAudio = false;
        bool dirtyScript = false;

        /* all the maps that stores the resources */
        // add the rig for skinning animation
        // add materials
        std::unordered_map<std::string, std::unique_ptr<Audio::AudioData>> audio;
        std::unordered_map<std::string, std::unique_ptr<Rendering::Model>> models;
        std::unordered_map<std::string, std::unique_ptr<Rendering::Texture>> textures;
        std::unordered_map<std::string, std::unique_ptr<std::string>> scripts;

        /* ************************************************************************* */
        std::vector<std::string> modelsKey;
        void UpdateModelsKey();
        std::vector<std::string> texturesKey;
        void UpdateTexturesKey();
        std::vector<std::string> audioKey;
        void UpdateAudioKey();
        std::vector<std::string> scriptKey;
        void UpdateScriptKey();

        Rendering::Texture* GetTexture(std::string path);
        Rendering::Model* GetModel(std::string path);
        Audio::AudioData* GetAudio(std::string path);
        std::string* GetScript(std::string path);


    };
}
#endif