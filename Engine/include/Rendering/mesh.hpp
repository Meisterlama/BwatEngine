#pragma once

#include <vector>
#include <string>
#include "shader.hpp"
#include "Math/Math.hpp"

namespace Rendering
{

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

struct Vertex
{
    BMath::vec3f postion;
    BMath::vec3f normal;
    BMath::vec2f texCoords;
    BMath::vec3f tangent;
    BMath::vec3f bitangent;
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