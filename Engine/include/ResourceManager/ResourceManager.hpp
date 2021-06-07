#ifndef RESOURCEMANAGER_RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_RESOURCEMANAGER_HPP_

#include <string>
#include <vector>
#include <unordered_map>
#include "Rendering/Model.hpp"
#include "Rendering/Texture.hpp"
#include "Audio/Sound.hpp"
#include "ECS/Components/ScriptComponent.hpp"

#include <filesystem>
#include <set>

namespace fs = std::filesystem;


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

        Rendering::Model* LoadModel(fs::path path);

        Rendering::Texture *LoadTexture(fs::path path);

        Audio::AudioData* LoadAudio(fs::path path);

        std::string* LoadScript(fs::path path);


        /* ************************************************************************* */

        /* get the resources with the type */

        Rendering::Model* GetOrLoadModel(fs::path path);

        Rendering::Texture* GetOrLoadTexture(fs::path path, Rendering::Texture::Type type = Rendering::Texture::Type::E_DIFFUSE);

        Audio::AudioData* GetOrLoadAudio(fs::path path);

        std::string* GetOrLoadScript(fs::path path);

        /* ************************************************************************* */

        std::set<fs::path>& GetModelList();

        std::set<fs::path>& GetTextList();

        std::set<fs::path>& GetAudioList();

        std::set<fs::path>& GetScriptList();

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
        std::set<fs::path> modelsKey;
        void UpdateModelsKey();
        std::set<fs::path> texturesKey;
        void UpdateTexturesKey();
        std::set<fs::path> audioKey;
        void UpdateAudioKey();
        std::set<fs::path> scriptKey;
        void UpdateScriptKey();

        Rendering::Texture* GetTexture(fs::path path);
        Rendering::Model* GetModel(fs::path path);
        Audio::AudioData* GetAudio(fs::path path);
        std::string* GetScript(fs::path path);


    };
}
#endif