#pragma once

#include "Math/Math.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Rendering
{
	struct VertexTriangle
	{
		BwatEngine::Math::Vec3f position;
		BwatEngine::Math::Vec4f color;
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

		BwatEngine::Math::Vec3f colorTriangle;
	};
}