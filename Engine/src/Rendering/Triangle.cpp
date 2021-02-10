
#include <imgui.h>
#include <cstdio>

#include "Triangle.hpp"

using namespace Rendering;
// Vertex

const char* vertexshaderStr = R"GLSL(
attribute vec3 position;

void main()
{
	gl_Position = vec4(position, 1.0);
}
)GLSL";

const char* pixelshaderStr = R"GLSL(

out vec4 fragColor;

uniform vec3 color;

void main()
{
	fragColor = vec4(color, 1.0);
}
)GLSL";


GLuint createShader(GLenum type, int sourceCount, const char** sources)
{
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, sourceCount, sources, nullptr);
	glCompileShader(shader);

	//debug shader
	GLint compileshader;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileshader);

	if (compileshader == GL_FALSE)
	{
		GLchar message[1024];
		glGetShaderInfoLog(shader, IM_ARRAYSIZE(message), nullptr, message);
		printf("Saherd compilation error : %s", message);
	}

	return shader;
}

Triangle::Triangle()
{
	//create Object

	//vertex buffer
	{
		Vertex triangleA[] =
		{
			{	Math::vec3f{ 0.5f, -0.5f, 0.0f}, Math::vec4f{ 1.f, 0.f, 0.f, 1.f} },
			{	Math::vec3f{-0.5f, -0.5f, 0.0f}, Math::vec4f{ 0.f, 1.f, 0.f, 1.f} },
			{	Math::vec3f{ 0.0f,  0.5f, 0.0f}, Math::vec4f{ 0.f, 0.f, 1.f, 1.f} },
		};

		glGenBuffers(1, &vertexbuffer);

		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangleA), triangleA, GL_STATIC_DRAW);
	}

	//Vertex Format
	{
		glGenVertexArrays(1, &vertexArray);

		glBindVertexArray(vertexArray);

		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, position));
	}

	//compile shader
	{
		program = glCreateProgram();

		const char* vertexShaderSource[] = {
			"#version 330\n",
			vertexshaderStr
		};

		const char* pixelShaderSource[] = {
			"#version 330\n",
			pixelshaderStr
		};

		GLuint vertexshader = createShader(GL_VERTEX_SHADER, IM_ARRAYSIZE(vertexShaderSource), vertexShaderSource);
		GLuint pixelshader = createShader(GL_FRAGMENT_SHADER, IM_ARRAYSIZE(pixelShaderSource), pixelShaderSource);
		
		glAttachShader(program, vertexshader);
		glAttachShader(program, pixelshader);
		glLinkProgram(program);

		GLint linkStatus;

		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE)
		{
			GLchar message[1024];
			glGetProgramInfoLog(program, IM_ARRAYSIZE(message), nullptr, message);
			printf("Program link error : %s", message);
		}

		glDeleteShader(vertexshader);
		glDeleteShader(pixelshader);
	}

}

Triangle::~Triangle()
{
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteBuffers(1, &vertexbuffer);
}



void Triangle::Update()
{
	//ImgUI
	float newcolor[3] = { colorTriangle.X, colorTriangle.Y, colorTriangle.Z };
	ImGui::ColorEdit3("Triangle color", newcolor);
	colorTriangle = { newcolor[0], newcolor[1], newcolor[2] };


	//use shader 
	glUseProgram(program);
	glUniform3f(glGetUniformLocation(program, "color"), newcolor[0], newcolor[1], newcolor[2]);

	//draw
	glBindVertexArray(vertexArray);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}