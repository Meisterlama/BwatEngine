#ifndef ENGINE_SERIALIZATION_HPP
#define ENGINE_SERIALIZATION_HPP




namespace BwatEngine
{
    class Scene;

    class Serializer
    {
    public:
        Serializer() = delete;
        ~Serializer() = default;
        Serializer(const char* path);

        void SaveScene(const Scene& toSave);
        void LoadData(Scene& toLoad);
    private:

        const char* path{""};


    };
}

#endif

