#include <cmath>

#include "Rendering/Model.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Debug/Logger.hpp"

using namespace Rendering;


Model::Model(const std::string &path)
{
    LoadModel(path);
};

void Model::LoadModel(const std::string& path)
{
    Assimp::Importer import;
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
        meshes.emplace_back(ProcessMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Rendering::Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    // data to fill
    std::vector<Rendering::Vertex> vertices;
    std::vector<unsigned int> indices;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Rendering::Vertex vertex;
        BwatEngine::Math::Vec3f vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::Vec3 first.
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
        // tangent
        if (mesh->HasTangentsAndBitangents())
        {
            vector.X = mesh->mTangents[i].x;
            vector.Y = mesh->mTangents[i].y;
            vector.Z = mesh->mTangents[i].z;
            vertex.tangent = vector;

            // bitangent
            vector.X = mesh->mBitangents[i].x;
            vector.Y = mesh->mBitangents[i].y;
            vector.Z = mesh->mBitangents[i].z;
            vertex.bitangent = vector;
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

    // 1. diffuse maps
    std::vector<Texture*> textures;
    std::vector<std::string> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    for (const std::string& path : diffuseMaps)
        textures.push_back(ResourceManager::Instance()->GetOrLoadTexture(path, Texture::Type::E_DIFFUSE));
    // 2. specular maps
    std::vector<std::string> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    for (const std::string& path : specularMaps)
        textures.push_back(ResourceManager::Instance()->GetOrLoadTexture(path, Texture::Type::E_SPECULAR));
    // 3. normal maps
    std::vector<std::string> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    for (const std::string& path : normalMaps)
        textures.push_back(ResourceManager::Instance()->GetOrLoadTexture(path, Texture::Type::E_NORMAL));
    // 4. height maps
    std::vector<std::string> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    for (const std::string& path : heightMaps)
        textures.push_back(ResourceManager::Instance()->GetOrLoadTexture(path, Texture::Type::E_HEIGHT));

    // return a mesh object created from the extracted mesh data
    return Rendering::Mesh(vertices, indices, textures);
}

std::vector<std::string> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<std::string> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        textures.push_back(directory + '/' + str.C_Str());
    }
    return textures;
}

void Model::Draw(Rendering::Shader& shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw(shader);
}

