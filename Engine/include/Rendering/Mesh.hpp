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
    };
    
    class Mesh
    {
    
    private:
    
        unsigned int VAO, VBO, EBO;
    
    public :
    
        // Data
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        Material defaultMaterial;
    
        // Constructor 
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, const Material& defaultMaterial);
        Mesh(const Mesh& mesh) = delete;
        ~Mesh();

        void Draw();
    
    };

}