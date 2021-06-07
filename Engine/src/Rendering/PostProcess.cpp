#include "Rendering/PostProcess.hpp"

using namespace Rendering;

PostProcess::PostProcess(Rendering::FullScreenQuad& fullScreenQuad)
	: fullScreenQuad(fullScreenQuad)
{

}

// ============================================ INVERSION ============================================ // 


Inversion::Inversion(Rendering::FullScreenQuad& fullScreenQuad)
	: PostProcess(fullScreenQuad)
	, shader({ "EngineAssets/Shaders/PostProcess/postProcess.vs", "EngineAssets/Shaders/PostProcess/inversion.fs" })
{
}

void Inversion::Draw(GLuint gameTexture)
{
	glBindTexture(GL_TEXTURE_2D, gameTexture);
	shader.Use();
	fullScreenQuad.Draw();
}

// ============================================ BLOOM ============================================ // 

Bloom::Bloom(Rendering::FullScreenQuad& fullScreenQuad,int width, int height)
	: PostProcess(fullScreenQuad)
	, shader({ "EngineAssets/Shaders/PostProcess/postProcess.vs", "EngineAssets/Shaders/PostProcess/bloom.fs" })
	, shaderGaussianBlur({ "EngineAssets/Shaders/PostProcess/postProcess.vs", "EngineAssets/Shaders/PostProcess/gaussianBlur.fs" })
	, shaderBloomFinal ({ "EngineAssets/Shaders/PostProcess/postProcess.vs", "EngineAssets/Shaders/PostProcess/bloomFinal.fs" })
{
	
	internalFBO.Resize(width, height);

	shaderBloomFinal.Use();
	shaderBloomFinal.SetInt("scene", 0);
	shaderBloomFinal.SetInt("bloomBlur", 1);

	glGenFramebuffers(2, pingpongFBO);
	glGenTextures(2, pingpongBuffer);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingpongBuffer[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongBuffer[i], 0);
	}
}

void Bloom::Draw(GLuint gameTexture)
{
	glBindTexture(GL_TEXTURE_2D, gameTexture);

	// Bind bloom internal fbo
	int previousFBO = internalFBO.Bind();
	
	shader.Use();
	fullScreenQuad.Draw();

	bool horizontal = true, first_iteration = true;
	int amount = 10;
	shaderGaussianBlur.Use();
	for (unsigned int i = 0; i < amount; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
		shaderGaussianBlur.SetInt("horizontal", horizontal);
		glBindTexture(
			GL_TEXTURE_2D, first_iteration ? internalFBO.textureColor.id : pingpongBuffer[!horizontal]
		);

		fullScreenQuad.Draw();
		horizontal = !horizontal;
		if (first_iteration)
			first_iteration = false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, previousFBO);

	shaderBloomFinal.Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gameTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, pingpongBuffer[!horizontal]);
	glActiveTexture(GL_TEXTURE0);
	shaderBloomFinal.SetFloat("exposure", exposure);
	fullScreenQuad.Draw();
}

// ============================================ BLUR ============================================ // 

Blur::Blur(Rendering::FullScreenQuad& fullscreenQuad)
	: PostProcess(fullscreenQuad)
	, shader({ "EngineAssets/Shaders/PostProcess/postProcess.vs", "EngineAssets/Shaders/PostProcess/blur.fs" })
{

}

void Blur::Draw(GLuint gameTexture) 
{
	glBindTexture(GL_TEXTURE_2D, gameTexture);
	shader.Use();
	fullScreenQuad.Draw();
}

// ============================================ GAMMA CORECTION ============================================ // 


GammaCorection::GammaCorection(Rendering::FullScreenQuad& fullscreenQuad)
	: PostProcess(fullscreenQuad)
	, shader({ "EngineAssets/Shaders/PostProcess/postProcess.vs", "EngineAssets/Shaders/PostProcess/gamma.fs" })
{

}

void GammaCorection::Draw(GLuint gameTexture) 
{
	glBindTexture(GL_TEXTURE_2D, gameTexture);
	shader.Use();
	fullScreenQuad.Draw();
}

