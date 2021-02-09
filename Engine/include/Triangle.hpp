#pragma once

#include "Math/vec3.h"
#include "Math/vec4.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


struct Vertex
{
	Vec3 position;
	Vec4 color;
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

	Vec3 colorTriangle;
};