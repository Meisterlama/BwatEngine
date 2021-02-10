#pragma once

#include <vector>
#include <string>
#include "shader.hpp"
#include "Math/Math.hpp"

namespace Rendering
{
    struct Vertex
    {
        Math::vec3f postion;
        Math::vec3f normal;
        Math::vec2f texCoords;
        Math::vec3f tangent;
        Math::vec3f bitangent;
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