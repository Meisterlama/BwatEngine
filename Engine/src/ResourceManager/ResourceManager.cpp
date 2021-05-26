#include "ResourceManager/ResourceManager.hpp"
#include "Debug/Logger.hpp"
#include <fstream>

namespace BwatEngine
{
    ResourceManager* ResourceManager::Instance()
    {
        static ResourceManager* instance = nullptr;
        if (instance == nullptr)
            instance = new ResourceManager;

        return instance;
    }

    Rendering::Model* ResourceManager::LoadModel(std::string path)
    {
        auto it = models.emplace(path, std::make_unique<Rendering::Model>(path));
        dirtyModels = true;
        return it.first->second.get();
    }

    Rendering::Texture * ResourceManager::LoadTexture(std::string path)
    {
        auto it = textures.emplace(path, std::make_unique<Rendering::Texture>(path));
        dirtyTextures = true;
        return it.first->second.get();
    }

    Audio::AudioData *ResourceManager::LoadAudio(std::string path)
    {
        auto it = audio.emplace(path, std::make_unique<Audio::AudioData>(path));
        dirtyAudio = true;
        return it.first->second.get();
    }

    std::string* ResourceManager::LoadScript(std::string path)
    {

        std::ifstream file (path, std::ios::binary | std::ios::ate);

        if(!file.is_open())
        {
            LogError("file cannot be open at path : %s", path.c_str());
            return nullptr;
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        auto it = scripts.emplace(path, std::make_unique<std::string>(size, '\0'));
        std::string& strData  = *it.first->second;
        file.read(strData.data(), size);
        file.close();

        dirtyScript = true;
        return it.first->second.get();
    }

    Rendering::Model* ResourceManager::GetOrLoadModel(std::string path)
    {
        Rendering::Model* res = ResourceManager::Instance()->GetModel(path);
        return (res != nullptr) ? res : LoadModel(path);
    }

    Rendering::Texture* ResourceManager::GetOrLoadTexture(std::string path, Rendering::Texture::Type type)
    {
        Rendering::Texture* res = ResourceManager::Instance()->GetTexture(path);
        return (res != nullptr) ? res : LoadTexture(path);
    }

    Audio::AudioData *ResourceManager::GetOrLoadAudio(std::string path)
    {
        Audio::AudioData* res = ResourceManager::Instance()->GetAudio(path);
        return (res != nullptr) ? res : LoadAudio(path);
    }

    std::string* ResourceManager::GetOrLoadScript(std::string path)
    {
        std::string* res = ResourceManager::Instance()->GetScript(path);
        return (res != nullptr) ? res : LoadScript(path);
    }

    std::vector<std::string>& ResourceManager::GetModelList()
    {
        if(dirtyModels)
            UpdateModelsKey();
        return modelsKey;
    }

    std::vector<std::string>& ResourceManager::GetTextList()
    {
        if (dirtyTextures)
            UpdateTexturesKey();
        return texturesKey;
    }

    std::vector<std::string> &ResourceManager::GetAudioList()
    {
        if (dirtyAudio)
            UpdateAudioKey();
        return audioKey;
    }

    std::vector<std::string>& ResourceManager::GetScriptList()
    {
        if (dirtyScript)
            UpdateScriptKey();
        return scriptKey;
    }

    void ResourceManager::UpdateModelsKey()
    {
        modelsKey.clear();
        for (auto &it : models)
        {
            modelsKey.push_back(it.first);
        }
        dirtyModels = false;
    }

    void ResourceManager::UpdateTexturesKey()
    {
        texturesKey.clear();
        for (auto &it : textures)
        {
            texturesKey.push_back(it.first);
        }
        dirtyTextures = false;
    }

    void ResourceManager::UpdateAudioKey()
    {
        audioKey.clear();
        for (auto &it : audio)
        {
            audioKey.push_back(it.first);
        }

        dirtyAudio = false;
    }

    void ResourceManager::UpdateScriptKey()
    {
        scriptKey.clear();
        for(auto &it : scripts)
        {
            scriptKey.push_back(it.first);
        }

        dirtyScript = false;
    }

    Rendering::Texture* ResourceManager::GetTexture(std::string path)
    {
        auto it = textures.find(path);
        if (it != textures.cend())
            return it->second.get();

        return nullptr;
    }

    Rendering::Model* ResourceManager::GetModel(std::string path)
    {
        auto it = models.find(path);
        if (it != models.cend())
            return it->second.get();

        return nullptr;
    }

    Audio::AudioData *ResourceManager::GetAudio(std::string path)
    {
        auto it = audio.find(path);
        if (it != audio.cend())
            return it->second.get();

        return nullptr;
    }

    std::string* ResourceManager::GetScript(std::string path)
    {
        auto it = scripts.find(path);
        if (it != scripts.cend())
            return it->second.get();

        return nullptr;
    }

}