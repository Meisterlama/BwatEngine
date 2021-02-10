#pragma once

#include "Math/Math.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Rendering
{
	struct Vertex
	{
		Math::vec3f position;
		Math::vec4f color;
	};

	class Triangle
	{
	public:
		Triangle();
		~Triangle();

		void Update();

	private:

		GLuint vertexbuffer;
		GLuint vertexArray;
		GLuint program;

		Math::vec3f colorTriangle;
	};
}