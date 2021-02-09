#pragma once

#include <vector>
#include "../Math/mat4.h"
#include "../Math/vec3.h"
#include "mesh.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.hpp"

#include "light.hpp"

//import assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



class Model
{
private:

		//Data
		
	std::vector<BwatRendering::Mesh> meshes;
	std::string directory;


	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	BwatRendering::Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<BwatRendering::Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);

public:
	
	Model(std::string &path)
	{ 
		LoadModel(path);
	};

	void Draw(Shader& shader);

};


