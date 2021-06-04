#pragma once

#include <vector>
#include "Shader.hpp"
#include "Math/Math.hpp"
#include "Material.hpp"

constexpr unsigned int MAX_BONE_INFLUENCE = 4;

namespace Rendering
{

    struct Vertex
    {
        Vertex()
        {
            for (int& boneID : boneIDs)
                boneID = -1;
            for (float& weight : weights)
                weight = 0.f;
        }
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
        int indexMaterial;
    
        // Constructor 
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material defaultMaterial , int indexMat = -1);
        Mesh(const Mesh& mesh) = delete;
        ~Mesh();

        void Draw();
    
    };
}