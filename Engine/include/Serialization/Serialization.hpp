#ifndef ENGINE_SERIALIZATION_HPP
#define ENGINE_SERIALIZATION_HPP

namespace BwatEngine
{
    class Scene;

    // namespace ou static
    namespace Serializer
    {
        void SaveScene(const char* path);
        void LoadScene(const char* path);
    };


};

#endif

