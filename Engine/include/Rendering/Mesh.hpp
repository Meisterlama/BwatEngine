#pragma once

#include <vector>
#include <string>
#include "Shader.hpp"
#include "Math/Math.hpp"
#include "Texture.hpp"
#include "Light.hpp"
#include "Material.hpp"

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
    Material material;

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