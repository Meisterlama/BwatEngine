#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <iostream>
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

		FrameBufferObject(float width, float height);
		FrameBufferObject() {};
		~FrameBufferObject() {};

		void UseAndBind();
		void Unbind();

		void SetName(std::string tmpName) { name = tmpName; };
		GLuint GetFbo() { return fbo; };

	};

}

#endif // !FRAMEBUFFER_HPP
