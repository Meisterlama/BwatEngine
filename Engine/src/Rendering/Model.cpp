#include <cmath>

#include "Rendering/Model.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Debug/Logger.hpp"


using namespace Rendering;

Model::Model(const std::string path)
{
    LoadModel(path);
};

void Model::LoadModel(const std::string path)
{
    modelPath = path;

    Assimp::Importer import; // be careful import is a c++ 20 keyword
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        LogError("ERROR::ASSIMP::%s\n", import.GetErrorString());
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        ProcessMesh(mesh, scene);
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    // data to fill
    std::vector<Rendering::Vertex> vertices;
    std::vector<unsigned int> indices;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Rendering::Vertex vertex;
        BwatEngine::Math::Vec3f vector; 

        // positions
        vector.X = mesh->mVertices[i].x;
        vector.Y = mesh->mVertices[i].y;
        vector.Z = mesh->mVertices[i].z;
        vertex.postion = vector;

        // normals
        if (mesh->HasNormals())
        {
            vector.X = mesh->mNormals[i].x;
            vector.Y = mesh->mNormals[i].y;
            vector.Z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }

        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            BwatEngine::Math::Vec2f vec;
            vec.X = mesh->mTextureCoords[0][i].x;
            vec.Y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
           
        }
        else
            vertex.texCoords = BwatEngine::Math::Vec2f(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    Rendering::Material myMaterial(*material);

    // return a mesh object created from the extracted mesh data
    meshes.emplace_back(std::make_unique<Mesh>(vertices, indices, myMaterial));
}

void Model::Draw(std::vector<Material*>* materials)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        if (materials)
            (*materials)[i]->Bind();
        else
            meshes[i]->defaultMaterial.Bind();

        meshes[i]->Draw();

    }
}

std::vector<Material*> Model::GetDefaultMaterials() const
{
    std::vector<Material*> materials;
    for (const auto& mesh : meshes)
        materials.push_back(&mesh->defaultMaterial);
    return materials;
}
