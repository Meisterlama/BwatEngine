#pragma once

#include <vector>
#include "mesh.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.hpp"
#include "light.hpp"

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
		std::vector<Texture> textures_loaded;
		std::vector<Mesh> meshes;
		std::string directory;


		void LoadModel(std::string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	public:

		Model(std::string& path);
		void Draw(Shader& shader, const std::vector<Light*> lights);

	};

}

