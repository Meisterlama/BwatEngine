#ifndef POSTPROCESSSYSTEM_HPP
#define POSTPROCESSSYSTEM_HPP

#include "ECS/System.hpp"
#include "ECS/ECS.hpp"

#include "Rendering/QuadScreen.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/FrameBuffer.hpp"
#include "Rendering/PostProcess.hpp"

#include "glad/glad.h"

#include <vector>

namespace BwatEngine
{
	

	class PostProcessSystem : public System
	{
	private:

		Rendering::FrameBufferObject framebuffer;
		Rendering::FullScreenQuad fullScreenQuad;

	
	public :

		Rendering::Inversion inversion;
		Rendering::Bloom bloom;
		Rendering::Blur blur;
		Rendering::GammaCorection gammaCor;

		bool isPostProcess = false;

		PostProcessSystem(int width, int height);

		void Begin();
		void Apply();
	};

}

#endif // !POSTPROCESSSYSTEM_HPP
