#ifndef CUBEMAP_HPP
#define CUBEMPA_HPP

#include <vector>
#include <string>

#include "glad/glad.h"
#include "Rendering/Shader.hpp"

namespace Rendering
{
	struct CubeMap
	{
		bool isDds = false;

		GLuint id;
		std::vector<std::string> faces;
		unsigned int skyboxVAO, skyboxVBO;
		Shader shader;

		void Init();
		void LoadCubeMap();
		void BindCubeMap();

		void LoadCubeMapDds(const char* filename);
		void UploadCubeMapDds(const char* filename);
		void BindAndDrawCubeMaDdsp();
		
	};
}

#endif // CUBEMAP_HPP