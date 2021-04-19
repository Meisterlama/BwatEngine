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

    Math::Vec3f position[maxIndex]{
        // Bottom
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

        {
            // Bottom
            indices.push_back(3), indices.push_back(1), indices.push_back(0),
            indices.push_back(3), indices.push_back(2), indices.push_back(1),

            // Left
            indices.push_back(3 + 4 * 1), indices.push_back(1 + 4 * 1), indices.push_back(0 + 4 * 1),
            indices.push_back(3 + 4 * 1), indices.push_back(2 + 4 * 1), indices.push_back(1 + 4 * 1),

            // Front                                                                                   
            indices.push_back(3 + 4 * 2), indices.push_back(1 + 4 * 2), indices.push_back(0 + 4 * 2),
            indices.push_back(3 + 4 * 2), indices.push_back(2 + 4 * 2), indices.push_back(1 + 4 * 2),

            // Back                                                                           
            indices.push_back(3 + 4 * 3), indices.push_back(1 + 4 * 3), indices.push_back(0 + 4 * 3),
            indices.push_back(3 + 4 * 3), indices.push_back(2 + 4 * 3), indices.push_back(1 + 4 * 3),

            // Right                                                                      
            indices.push_back(3 + 4 * 4), indices.push_back(1 + 4 * 4), indices.push_back(0 + 4 * 4),
            indices.push_back(3 + 4 * 4), indices.push_back(2 + 4 * 4), indices.push_back(1 + 4 * 4),

            //TOP
            indices.push_back(3 + 4 * 5), indices.push_back(1 + 4 * 5), indices.push_back(0 + 4 * 5),
            indices.push_back(3 + 4 * 5), indices.push_back(2 + 4 * 5), indices.push_back(1 + 4 * 5);

        }

    for (int i = 0; i < maxIndex; i++)
    {
        Vertex vertex;
        vertex.position = position[i];
        vertex.normal = normales[i];
        vertex.texCoord = uvs[i];

        vertices.push_back(vertex);
    }

    Material mat;
    Model model;
    model.AddMesh(vertices, indices, mat);

    return model;
}

Model CreateSphere(int latitudeCount , int longitudeCount )
{
    // position all point of sphere
    float z = 1.f;
    float subdiv = Math::PI / latitudeCount;
    float radius;
    float x, y;


    std::vector<unsigned int> indices;
    std::vector<Math::Vec3f> positions;

    std::vector<Math::Vec3f> normals;
    std::vector<Math::Vec2f> uvs;

    positions.push_back(Math::Vec3f(.0f, 1.f, .0f));

    for (int i = 0; i < latitudeCount; i++)
    {
        for (int j = 0; j < longitudeCount; j++)
        {
            radius = sin(i * subdiv);
            y = cos(i * subdiv);
            x = cos(j * (2 * Math::PI) / longitudeCount) * radius;
            z = sin(j * (2 * Math::PI) / longitudeCount) * radius;
            positions.push_back(Math::Vec3f(x, y, z));
        }
    }

    positions.push_back({ .0f, -1.f, .0f });

   for (int n = 0; n < positions.size(); n++)
       normals.push_back(positions[n].Normalize());

   uvs.push_back((0, 1));
   for (int lat = 0; lat < latitudeCount; lat++)
       for (int lon = 0; lon <= longitudeCount; lon++)
           uvs.push_back(((float)lon / longitudeCount, 1.f - (float)(lat + 1) / (latitudeCount + 1)));
   uvs.push_back((0, 0));


    // draw all triangle with good order 
    for (int i = 0; i < longitudeCount; ++i)
    {
        float a = i + 1;
        float b = (i + 1) % longitudeCount + 1;
        indices.push_back(0);
        indices.push_back(a);
        indices.push_back(b);
    }


    for (int i = 0; i < latitudeCount - 1; ++i)
    {
        float astart = i * longitudeCount + 1;
        float bstart = (i + 1) * longitudeCount + 1;

        for (int j = 0; j < longitudeCount; ++j)
        {
            float a = astart + j;
            float a1 = astart + (j + 1) % longitudeCount;
            float b = bstart + j;
            float b1 = bstart + (j + 1) % longitudeCount;

            //// first triangle
            indices.push_back(a);
            indices.push_back(a1);
            indices.push_back(b1);

            //// second triangle
            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(b1);
        }
    }

    for (int i = 0; i < longitudeCount; ++i)
    {
        float a = i + longitudeCount * (latitudeCount - 1) + 1;
        float b = (i + 1) % longitudeCount +
            longitudeCount * (latitudeCount - 1) + 1;

        indices.push_back(positions.size() - 1);
        indices.push_back(a);
        indices.push_back(b);
    }

    std::vector<Vertex> vertices;

    for (int i = 0; i < positions.size() ; i++)
    {
        Vertex vertex;
        vertex.position = positions[i];
        vertex.normal = normals[i];
        vertex.texCoord = uvs[i];

        vertices.push_back(vertex);
    }

    Material mat;
    Model model;
    model.AddMesh(vertices, indices, mat);

    return model;
}

Model CreatePlan()
{

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    float length = 1.f;
    float width = 1.f;
    int resX = 2; // 2 minimum
    int resZ = 2;
    
    Math::Vec3f position[4]{};

    for (int z = 0; z < resZ; z++)
    {
        // [ -length / 2, length / 2 ]
        float zPos = ((float)z / (resZ - 1) - .5f) * length;
        for (int x = 0; x < resX; x++)
        {
            // [ -width / 2, width / 2 ]
            float xPos = ((float)x / (resX - 1) - .5f) * width;
            position[x + z * resX] = Math::Vec3f(xPos, 0.f, zPos);
        }
    }
 
    Math::Vec3f  normals[4];

    for (int n = 0; n < 4; n++)
        normals[n] = position[n].Normalize();

    Math::Vec2f uvs[4]; 

    for (int v = 0; v < resZ; v++)
    {
        for (int u = 0; u < resX; u++)
        {
            uvs[u + v * resX] = Math::Vec2f((float)u / (resX - 1), (float)v / (resZ - 1));
        }
    }
   
    int triangles[12];
    int t = 0;
    for (int face = 0; face < 2; face++)
    {
        int i = face % (resX - 1) + (face / (resZ - 1) * resX);

        triangles[t++] = i + resX;
        triangles[t++] = i + 1;
        triangles[t++] = i;

        triangles[t++] = i + resX;
        triangles[t++] = i + resX + 1;
        triangles[t++] = i + 1;
    }

    for (int i = 0; i < 12; i++)
        indices.push_back(triangles[i]);

    for (int i = 0; i < 4; i++)
    {
        Vertex vertex;
        vertex.position = position[i];
        vertex.normal = normals[i];
        vertex.texCoord = uvs[i];

        vertices.push_back(vertex);
    }

    Material mat;
    Model model;
    model.AddMesh(vertices, indices, mat);

    return model;
}