#include "Rendering/Primitives.hpp"

using namespace Rendering;
using namespace BwatEngine;

Model CreateCube()
{
    const int maxIndex = 24;

    float length = 1.f;
    float width = 1.f;
    float height = 1.f;

	std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // position
    Math::Vec3f p0 (-length * .5f, -width * .5f, height * .5f);
    Math::Vec3f p1 (length * .5f, -width * .5f, height * .5f);
    Math::Vec3f p2 (length * .5f, -width * .5f, -height * .5f);
    Math::Vec3f p3(-length * .5f, -width * .5f, -height * .5f);
    Math::Vec3f p4 (-length * .5f, width * .5f, height * .5f);
    Math::Vec3f p5 (length * .5f, width * .5f, height * .5f);
    Math::Vec3f p6 (length * .5f, width * .5f, -height * .5f);
    Math::Vec3f p7 (-length * .5f, width * .5f, -height * .5f);

    Math::Vec3f position[maxIndex]{// Bottom
    p0, p1, p2, p3,

    // Left
    p7, p4, p0, p3,

    // Front
    p4, p5, p1, p0,

    // Back
    p6, p7, p3, p2,

    // Right
    p5, p6, p2, p1,

    // Top
    p7, p6, p5, p4 };

    // normal
    Math::Vec3f up (0,1,0);
    Math::Vec3f down (0,-1,0);
    Math::Vec3f front (0,0,1);
    Math::Vec3f back (0,0,-1);
    Math::Vec3f left (-1,0,0);
    Math::Vec3f right (1,0,0);

    Math::Vec3f normales[maxIndex]{// Bottom
    down, down, down, down,

    // Left
    left, left, left, left,

    // Front
    front, front, front, front,

    // Back
    back, back, back, back,

    // Right
    right, right, right, right,

    // Top
    up, up, up, up
    };

    // UV
    Math::Vec2f _00 (0.f, 0.f);
    Math::Vec2f _10 (1.f, 0.f);
    Math::Vec2f _01 (0.f, 1.f);
    Math::Vec2f _11 (1.f, 1.f);

    Math::Vec2f uvs[maxIndex]
    {
        // Bottom
        _11, _01, _00, _10,

        // Left
        _11, _01, _00, _10,

        // Front
        _11, _01, _00, _10,

        // Back
        _11, _01, _00, _10,

        // Right
        _11, _01, _00, _10,

        // Top
        _11, _01, _00, _10,
    };

    for (int i = 0; i < maxIndex; i++)
    {
        Vertex vertex;
        vertex.postion = position[i];
        vertex.normal = normales[i];
        vertex.texCoords = uvs[i];

        vertices.push_back(vertex);
        indices.push_back(i);
    }

    Material mat;
    Model model;
    // attention au material en const ref 
    model.AddMesh(vertices, indices, mat);

    return model;
}

void CreateSphere()
{

}

void CreatePlan()
{

}