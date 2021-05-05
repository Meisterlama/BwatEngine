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
		GLuint id;
		std::vector<std::string> faces;
		unsigned int skyboxVAO, skyboxVBO;
		Shader shader;

		void Init();
		void LoadCubeMap();
		void BindCubeMap();
	};
}

#endif // CUBEMAP_HPP