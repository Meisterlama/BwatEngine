#pragma once

#include <vector>
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

	class Model
	{
	private:

		//Data
		std::vector<Texture> textures_loaded{};
		std::vector<std::string> tex;
		std::vector<Mesh> meshes{};
		std::string directory{};


		void LoadModel(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<std::string> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	public:

        Model() = default;
        Model(const std::string &path);
		    void Draw(Shader& shader);

	};

}

