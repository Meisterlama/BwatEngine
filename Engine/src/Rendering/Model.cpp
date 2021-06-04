#include <cmath>
#include <filesystem>

#include "Rendering/Model.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Debug/Logger.hpp"


using namespace Rendering;

Model::Model(const std::string& path)
{
    LoadModel(path);
};

void Model::LoadModel(const std::string& path)
{
    modelPath = path;

    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate ); // | aiProcess_FlipUVs

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        LogError("ERROR::ASSIMP::%s\n", import.GetErrorString());
        return;
    }

    std::filesystem::path filePath = path;
    ProcessNode((filePath.parent_path().string() + "/").c_str(), scene->mRootNode, scene);
}

void Model::ProcessNode(const std::string& basePath, aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        ProcessMesh(basePath, mesh, scene);
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(basePath, node->mChildren[i], scene);
    }
}

void Model::ProcessMesh(const std::string& basePath, aiMesh* mesh, const aiScene* scene)
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
        vertex.position = vector;

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
            vertex.texCoord = vec;
           
        }
        else
            vertex.texCoord = BwatEngine::Math::Vec2f(0.0f, 0.0f);


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

    Rendering::Material myMaterial(basePath.c_str(), *material);

    ExtractBoneWeightForVertices(vertices, mesh, scene);

    // return a mesh object created from the extracted mesh data
    meshes.emplace_back(std::make_unique<Mesh>(vertices, indices, myMaterial, mesh->mMaterialIndex));
}

void Model::Draw(Shader& shader, std::vector<Material*>* materials)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        if (materials != nullptr && materials->size() > i && (*materials)[i] != nullptr)
        {
            (*materials)[i]->ApplyToShader(shader);
            (*materials)[i]->Bind();
        }
        else
        {
            meshes[i]->defaultMaterial.ApplyToShader(shader);
            meshes[i]->defaultMaterial.Bind();
        }

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

void Model::AddMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,Material material)
{
    meshes.emplace_back(std::make_unique<Mesh>(vertices, indices, material));
}

// ============================= Bones ============================= //

void Model::SetVertexBoneDataToDefault(Vertex& vertex)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
    {
        vertex.boneIDs[i] = -1;
        vertex.weights[i] = 0.0f;
    }
}

void SetVertexBoneData(Vertex& vertex, int boneID, float weight)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
    {
        if (vertex.boneIDs[i] < 0)
        {
            vertex.weights[i] = weight;
            vertex.boneIDs[i] = boneID;
            break;
        }
    }
}


static BwatEngine::Math::Mat4f ConvertMatrixToBFormat(const aiMatrix4x4& from)
{
    BwatEngine::Math::Mat4f to;
    memcpy(to.values, &from.a1, sizeof(BwatEngine::Math::Mat4f));
    return to.GetTransposed();
}
void Model::ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh,const aiScene* scene)
{
    for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
    {
        int boneID = -1;
        std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
        if (boneInfoMap.find(boneName) == boneInfoMap.end())
        {
            BoneInfo newBoneInfo;
            newBoneInfo.id = boneCounter;
            // MAYBE need Transpose //
            newBoneInfo.offset = ConvertMatrixToBFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
            boneInfoMap[boneName] = newBoneInfo;
            boneID = boneCounter;
            boneCounter++;
        }
        else
        {
            boneID = boneInfoMap[boneName].id;
        }
        assert(boneID != -1);
        auto weights = mesh->mBones[boneIndex]->mWeights;
        int numWeights = mesh->mBones[boneIndex]->mNumWeights;

        for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
        {
            int vertexId = weights[weightIndex].mVertexId;
            float weight = weights[weightIndex].mWeight;
            assert(vertexId <= vertices.size());
            SetVertexBoneData(vertices[vertexId], boneID, weight);
        }
    }
}