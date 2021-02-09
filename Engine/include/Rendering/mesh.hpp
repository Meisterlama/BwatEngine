#pragma once

#include <vector>
#include <string>
#include "shader.hpp"
#include "../Math/vec2.h"
#include "../Math/vec3.h"

namespace BwatRendering
{
    struct Vertex
    {
        Vec3 postion;
        Vec3 normal;
        Vec2 texCoords;
        Vec3 tangent;
        Vec3 bitangent;
    };


struct Texture
{
    unsigned int id;
    std::string type;
};

class Mesh
{

private:

    void initMesh();
    unsigned int VAO, VBO, EBO;

public :

    // Data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // Constructor 
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    void Draw(Shader& shader);


};

}