#ifndef POSTPROCESS_HPP
#define POSTPROCESS_HPP

#include "Rendering/Shader.hpp"

namespace Rendering
{
	class PostProcess
	{
	public:

		void Init();
		void Apply(GLuint texColorFBO);

		unsigned int quadVAO, quadVBO ;
	};
}

#endif //POSTPROCESS_HPP