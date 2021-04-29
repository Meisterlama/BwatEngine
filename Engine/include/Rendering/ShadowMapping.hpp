#ifndef SHADOWMAPPING_HPP
#define SHADOWMAPPING_HPP

#include "Rendering/Shader.hpp"

namespace Rendering 
{
	class ShadowMapping
	{
	private:

	public:

		ShadowMapping(int width = 1024, int  height = 1024);

		Shader shader;
		int width, height;
		unsigned int depthMapFbo;
		unsigned int depthMap;
	};

}

#endif // SHADOWMAPPING_HPP