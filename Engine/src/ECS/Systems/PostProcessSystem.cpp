#include "ECS/Systems/PostProcessSystem.hpp"

using namespace BwatEngine;

PostProcessSystem::PostProcessSystem(int width, int height)
	: inversion(fullScreenQuad)
	, bloom(fullScreenQuad,width,height)
	, blur(fullScreenQuad)
	, gammaCor(fullScreenQuad)
{
	framebuffer.Resize(width, height);

	inversion.SetEnabled(false);
	bloom.SetEnabled(false);
	blur.SetEnabled(false);
	gammaCor.SetEnabled(true);

	shaderPP = { "EngineAssets/Shaders/PostProcess/postProcess.vs", "EngineAssets/Shaders/PostProcess/basicPP.fs" };
}

void PostProcessSystem::Begin()
{
	framebuffer.Bind();
}

void PostProcessSystem::Apply()
{
	GLint targetFramebuffer;
	glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &targetFramebuffer);

	glDisable(GL_DEPTH_TEST);

	Rendering::PostProcess* postProcesses[] = {
		&inversion,
		&bloom,
		&blur,
		&gammaCor
	};

	// Select only enabled post processes
	std::vector<Rendering::PostProcess*> enabledPostProcesses;
	for (Rendering::PostProcess* postProcess : postProcesses)
		if (postProcess->IsEnabled())
			enabledPostProcesses.push_back(postProcess);

	if (enabledPostProcesses.empty())
		return;

	Rendering::FrameBufferObject* target = nullptr;
	for (int i = 0; i < enabledPostProcesses.size(); ++i)
	{
		Rendering::FrameBufferObject* source = (i == 0) ? &framebuffer : &fbo[i % 2];
		target = &fbo[(i + 1) % 2];

		glBindFramebuffer(GL_FRAMEBUFFER, target->fbo);
		enabledPostProcesses[i]->Draw(source->textureColor.id);
	}

	if (target == nullptr) // Impossible, but suppress warning
		return;

	glBindFramebuffer(GL_FRAMEBUFFER, targetFramebuffer);
	glBindTexture(GL_TEXTURE_2D, target->textureColor.id);
	shaderPP.Use();
	fullScreenQuad.Draw();


}