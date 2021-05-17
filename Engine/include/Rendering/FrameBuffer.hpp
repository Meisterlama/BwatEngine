#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <glad/glad.h>

#include "Texture.hpp"

namespace Rendering
{

	class FrameBufferObject
	{

	public:

		std::string name;
		GLuint fbo;
		Texture textureColor;
		GLuint depthRenderbuffer;

		FrameBufferObject(int width = 1200, int height = 720);
		~FrameBufferObject() {};

		GLint Bind();

		void Resize(float width, float height);
		void SetName(std::string tmpName) { name = tmpName; };
		GLuint GetFbo() { return fbo; };

	};

}

#endif // !FRAMEBUFFER_HPP
