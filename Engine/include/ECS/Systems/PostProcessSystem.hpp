#ifndef POSTPROCESSSYSTEM_HPP
#define POSTPROCESSSYSTEM_HPP

#include "ECS/System.hpp"
#include "ECS/ECS.hpp"

#include "Rendering/PostProcess.hpp"
#include "Rendering/Shader.hpp"

#include "glad/glad.h"

#include <vector>

namespace BwatEngine
{
	enum POSTPROCESS_SHADER
	{
		INVERSION,
		KERNELCLASSIC,
		BLUR,
		EDGE,
		CUSTOM,
		SIZE,
	};

	class PostProcessSystem : public System
	{
	private:

		Rendering::Shader customShader;
		Rendering::PostProcess postProcess;
		std::vector<Rendering::Shader> shaders;
	
	public :

		void Update(GLuint textureID, POSTPROCESS_SHADER indexShader);
		void Init();
	};

}

#endif // !POSTPROCESSSYSTEM_HPP
