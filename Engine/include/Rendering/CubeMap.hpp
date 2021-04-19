#ifndef CUBEMAP_HPP
#define CUBEMPA_HPP

#include <vector>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Rendering
{
	struct CubeMap
	{
		GLuint id;
		std::vector<std::string> faces;
		unsigned int skyboxVAO, skyboxVBO;

		void Init();
		void LoadCubeMap();
		void BindCubeMap();
	};
}

#endif // CUBEMAP_HPP