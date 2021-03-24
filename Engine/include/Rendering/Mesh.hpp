#pragma once

#include <vector>
#include <string>
#include "shader.hpp"
#include "Math/Math.hpp"
#include "texture.hpp"
#include "light.hpp"

namespace Rendering
{

struct Vertex
{
    BwatEngine::Math::Vec3f postion;
    BwatEngine::Math::Vec3f normal;
    BwatEngine::Math::Vec2f texCoords;
    BwatEngine::Math::Vec3f tangent;
    BwatEngine::Math::Vec3f bitangent;
};

class Mesh
{
private:
    bool loaded = false;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

public:
    // Data
    //std::vector<Vertex> vertices;
    //std::vector<unsigned int> indices;
    int indiceCount;
    std::vector<Texture*> textures;

    // Constructor
    Mesh(const Mesh& other) = delete;
    Mesh(Mesh&& other);
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture*>& textures);
    ~Mesh();

    void Draw(Shader& shader);


};

}