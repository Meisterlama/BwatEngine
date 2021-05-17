#ifndef QUADSCREEN_HPP
#define QUADSCREEN_HPP

#include "Rendering/Shader.hpp"

namespace Rendering
{
	class FullScreenQuad
	{
	public:
		FullScreenQuad();
		~FullScreenQuad();
		void Draw();

	private:
		unsigned int quadVAO, quadVBO ;
	};
}

#endif //QUADSCREEN_HPP