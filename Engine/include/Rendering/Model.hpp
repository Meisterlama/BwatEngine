#pragma once

#include <vector>
#include <memory>
#include <filesystem>
#include "Mesh.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.hpp"
#include "Light.hpp"

#include "Math/Math.hpp"

//import assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Rendering
{
	class Material;

	class Model
	{
	private:

		//Data
		std::vector<std::unique_ptr<Mesh>> meshes;
		std::string directory{};

		void LoadModel(const std::string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);

	public:

	    std::filesystem::path modelPath;

        Model() = default;
        Model(const std::string path);

		void AddMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, const Material& material);
		std::vector<Material*> GetDefaultMaterials() const;
		void Draw(std::vector<Material*>* materials = nullptr);
	};

}

