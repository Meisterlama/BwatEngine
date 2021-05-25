#pragma once

#include <vector>
#include "Shader.hpp"
#include "Math/Math.hpp"
#include "Material.hpp"

#define MAX_BONE_INFLUENCE 4

namespace Rendering
{

    struct Vertex
    {
        BwatEngine::Math::Vec3f position;
        BwatEngine::Math::Vec3f normal;
        BwatEngine::Math::Vec2f texCoord;

        int boneIDs[MAX_BONE_INFLUENCE];
        float weights[MAX_BONE_INFLUENCE];
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
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material defaultMaterial);
        Mesh(const Mesh& mesh) = delete;
        ~Mesh();

        void Draw();
    
    };
}