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
	gammaCor.SetEnabled(false);
}

void PostProcessSystem::Begin()
{
	framebuffer.Bind();
}

void PostProcessSystem::Apply()
{
	glDisable(GL_DEPTH_TEST);

	Rendering::PostProcess* postProcesses[] = {
		&inversion,
		&bloom,
		&blur,
		&gammaCor
	};

	for (Rendering::PostProcess* postProcess : postProcesses)
	{
		if (postProcess->IsEnabled())
			postProcess->Draw(framebuffer.textureColor.id);
	}
}