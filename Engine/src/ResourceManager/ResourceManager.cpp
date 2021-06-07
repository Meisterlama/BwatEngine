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

    Rendering::Model* ResourceManager::LoadModel(fs::path path)
    {
        auto it = models.emplace(path.string(), std::make_unique<Rendering::Model>(path.string()));
        dirtyModels = true;
        return it.first->second.get();
    }

    Rendering::Texture * ResourceManager::LoadTexture(fs::path path)
    {
        auto it = textures.emplace(path.string(), std::make_unique<Rendering::Texture>(path.string()));
        dirtyTextures = true;
        return it.first->second.get();
    }

    Audio::AudioData *ResourceManager::LoadAudio(fs::path path)
    {
        auto it = audio.emplace(path.string(), std::make_unique<Audio::AudioData>(path.string()));
        dirtyAudio = true;
        return it.first->second.get();
    }

    std::string* ResourceManager::LoadScript(fs::path path)
    {

        std::ifstream file (path, std::ios::binary | std::ios::ate);

        if(!file.is_open())
        {
            LogError("file cannot be open at path : %s", path.string().c_str());
            return nullptr;
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        auto it = scripts.emplace(path.string(), std::make_unique<std::string>(size, '\0'));
        std::string& strData  = *it.first->second;
        file.read(strData.data(), size);
        file.close();

        dirtyScript = true;
        return it.first->second.get();
    }

    Rendering::Model* ResourceManager::GetOrLoadModel(fs::path path)
    {
        if (path.empty())
            return nullptr;
        path.make_preferred();

        Rendering::Model* res = ResourceManager::Instance()->GetModel(path);
        return (res != nullptr) ? res : LoadModel(path);
    }

    Rendering::Texture* ResourceManager::GetOrLoadTexture(fs::path path, Rendering::Texture::Type type)
    {
        if (path.empty())
            return nullptr;
        path.make_preferred();

        Rendering::Texture* res = ResourceManager::Instance()->GetTexture(path);
        return (res != nullptr) ? res : LoadTexture(path);
    }

    Audio::AudioData *ResourceManager::GetOrLoadAudio(fs::path path)
    {
        if (path.empty())
            return nullptr;
        path.make_preferred();

        Audio::AudioData* res = ResourceManager::Instance()->GetAudio(path);
        return (res != nullptr) ? res : LoadAudio(path);
    }

    std::string* ResourceManager::GetOrLoadScript(fs::path path)
    {
        if (path.empty())
            return nullptr;
        path.make_preferred();

        std::string* res = ResourceManager::Instance()->GetScript(path);
        return (res != nullptr) ? res : LoadScript(path);
    }

    std::set<fs::path>& ResourceManager::GetModelList()
    {
        if(dirtyModels)
            UpdateModelsKey();
        return modelsKey;
    }

    std::set<fs::path>& ResourceManager::GetTextList()
    {
        if (dirtyTextures)
            UpdateTexturesKey();
        return texturesKey;
    }

    std::set<fs::path> &ResourceManager::GetAudioList()
    {
        if (dirtyAudio)
            UpdateAudioKey();
        return audioKey;
    }

    std::set<fs::path>& ResourceManager::GetScriptList()
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
            modelsKey.insert(it.first);
        }
        dirtyModels = false;
    }

    void ResourceManager::UpdateTexturesKey()
    {
        texturesKey.clear();
        for (auto &it : textures)
        {
            texturesKey.insert(it.first);
        }
        dirtyTextures = false;
    }

    void ResourceManager::UpdateAudioKey()
    {
        audioKey.clear();
        for (auto &it : audio)
        {
            audioKey.insert(it.first);
        }

        dirtyAudio = false;
    }

    void ResourceManager::UpdateScriptKey()
    {
        scriptKey.clear();
        for(auto &it : scripts)
        {
            scriptKey.insert(it.first);
        }

        dirtyScript = false;
    }

    Rendering::Texture* ResourceManager::GetTexture(fs::path path)
    {
        auto it = textures.find(path.string());
        if (it != textures.cend())
            return it->second.get();

        return nullptr;
    }

    Rendering::Model* ResourceManager::GetModel(fs::path path)
    {
        auto it = models.find(path.string());
        if (it != models.cend())
            return it->second.get();

        return nullptr;
    }

    Audio::AudioData *ResourceManager::GetAudio(fs::path path)
    {
        auto it = audio.find(path.string());
        if (it != audio.cend())
            return it->second.get();

        return nullptr;
    }

    std::string* ResourceManager::GetScript(fs::path path)
    {
        auto it = scripts.find(path.string());
        if (it != scripts.cend())
            return it->second.get();

        return nullptr;
    }

}