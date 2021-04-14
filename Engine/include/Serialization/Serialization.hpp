#ifndef ENGINE_SERIALIZATION_HPP
#define ENGINE_SERIALIZATION_HPP




namespace BwatEngine
{
    class Scene;

    // namespace ou static
    namespace Serializer
    {
        void SaveScene(const Scene& toSave, const char* path);
        void LoadScene(Scene& toLoad, const char* path);
    };


};

#endif

