#pragma once

#include "Math/Math.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Rendering
{
	struct VertexTriangle
	{
		BMath::vec3f position;
		BMath::vec4f color;
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

		BMath::vec3f colorTriangle;
	};
}