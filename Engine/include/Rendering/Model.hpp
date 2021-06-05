#pragma once

#include <memory>
#include <vector>
#include <map>
#include <string>
#include "Mesh.hpp"
#include "glad/glad.h"
#include "Shader.hpp"

#include "Math/Math.hpp"

//import assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Rendering
{
	class Material;

	struct BoneInfo
	{
		int id;
		BwatEngine::Math::Mat4f offset;
	};

	class Model
	{
	private:

		//Data
		std::vector<std::unique_ptr<Mesh>> meshes;

		std::map<std::string, BoneInfo> boneInfoMap; 
		int boneCounter = 0;

		void LoadModel(const std::string& path);
		void ProcessNode(const std::string& basePath, aiNode* node, const aiScene* scene);
		void ProcessMesh(const std::string& basePath, aiMesh* mesh, const aiScene* scene);
		//bones
		void SetVertexBoneDataToDefault(Vertex& vertex);
		void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);

	public:

	    std::string modelPath;

        Model() = default;
        Model(const std::string& path);

		void AddMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,Material material);
		std::vector<Material*> GetDefaultMaterials() const;
		void Draw(Shader& shader, std::vector<Material*>* materials = nullptr);

    void DrawWireFrame(std::vector<Material *> *materials = nullptr);
    
		std::map<std::string, BoneInfo>& GetBoneInfoMap() { return boneInfoMap; };
		int& GetBoneCount() { return boneCounter; };
	};

}

