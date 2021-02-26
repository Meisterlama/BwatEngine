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

    void initMesh();
    unsigned int VAO, VBO, EBO;

public :

    // Data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // Constructor 
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    void Draw(Shader& shader, const std::vector<Light*> lights);


};

}