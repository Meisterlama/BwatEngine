#ifndef RESOURCEMANAGER_RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_RESOURCEMANAGER_HPP_

#include "Rendering/Model.hpp"
#include <unordered_map>

class ResourceManager
{
public:
    /* the instance for the singleton */

    static ResourceManager* Instance()
    {
        return instance;
    }



    /* ************************************************************************* */

    /* constructors */

    ResourceManager();

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager operator=(const ResourceManager) = delete;

    /* ************************************************************************* */

    /* All the load resources with template to call and stock on the good map */

    template<typename T>
    void LoadResource(const char* path);
/*
    template<>
    void LoadResource<SoundResource>(const char* path);
*/
    template<>
    void LoadResource<Rendering::Model>(const char* path);

    template<>
    void LoadResource<Rendering::Texture>(const char* path);

    /* ************************************************************************* */

    /* get the resources with the template type */

    template<typename T>
    T* GetResource(const char* path);
/*
    template<>
    T* GetResource<SoundResource>(const char* path);
*/
    template<>
    Rendering::Model* GetResource<Rendering::Model>(const char* path);

    template<>
    Rendering::Texture* GetResource<Rendering::Texture>(const char* path);

    /* ************************************************************************* */

private:

    static ResourceManager* instance;

    /* all the maps that stores the resources */
    // add the rig for skinning animation
    // add materials
    //std::unordered_map<std::string, SoundResource> sounds;
    std::unordered_map<std::string, Rendering::Model> models;
    std::unordered_map<std::string, Rendering::Texture> textures;

    /* ************************************************************************* */


};


#endif








