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

		FrameBufferObject(float width = 1200, float height = 720);
		~FrameBufferObject() {};

		void UseAndBind();
		void Unbind();

		void Rezise(float width, float height);
		void SetName(std::string tmpName) { name = tmpName; };
		GLuint GetFbo() { return fbo; };

	};

}

#endif // !FRAMEBUFFER_HPP
