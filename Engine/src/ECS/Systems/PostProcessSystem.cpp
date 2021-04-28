#include "ECS/Systems/PostProcessSystem.hpp"

using namespace BwatEngine;

void PostProcessSystem::Init()
{
	postProcess.Init();

	shaders.push_back({ "Assets/Shaders/PostProcess/postProcess.vs", "Assets/Shaders/PostProcess/inversion.fs" });
	shaders.push_back({ "Assets/Shaders/PostProcess/postProcess.vs", "Assets/Shaders/PostProcess/kernel.fs" });
	shaders.push_back({ "Assets/Shaders/PostProcess/postProcess.vs", "Assets/Shaders/PostProcess/blur.fs" });
	shaders.push_back({ "Assets/Shaders/PostProcess/postProcess.vs", "Assets/Shaders/PostProcess/edge.fs" });
}

void PostProcessSystem::Update(GLuint textureID , POSTPROCESS_SHADER indexShader)
{
	glDisable(GL_DEPTH_TEST);

	shaders[indexShader].use();

	postProcess.Apply(textureID);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}