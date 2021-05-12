#ifndef POSTPROCESS_HPP
#define POSTPROCESS_HPP

#include <glad/glad.h>
#include "Rendering/Shader.hpp"
#include "Rendering/QuadScreen.hpp"
#include "Rendering/FrameBuffer.hpp"

namespace Rendering
{
	class PostProcess
	{
	public:
		PostProcess(FullScreenQuad& fullScreenQuad);

		virtual ~PostProcess() = default;
		virtual void Draw(GLuint gameTexture) = 0;

		bool IsEnabled() const { return enabled; }
		void SetEnabled(bool enabled) { this->enabled = enabled; }

	protected:
		bool enabled = false;
		Rendering::FullScreenQuad& fullScreenQuad;
	};


	// ============================================ INVERSION ============================================ // 

	class Inversion : public PostProcess
	{
	public:
		Inversion(Rendering::FullScreenQuad& fullscreenQuad);
		void Draw(GLuint gameTexture) override;

	private:
		Rendering::Shader shader;
	};

	// ============================================ BLOOM ============================================ // 

	class Bloom : public PostProcess
	{
	public:
		Bloom(Rendering::FullScreenQuad& fullscreenQuad,int width, int height);
		void Draw(GLuint gameTexture) override;

	private:
		Rendering::FrameBufferObject internalFBO;

		unsigned int pingpongFBO[2];
		unsigned int pingpongBuffer[2];

		Rendering::Shader shader;
		Rendering::Shader shaderGaussianBlur;
		Rendering::Shader shaderBloomFinal;
	};
	
	// ============================================ BLUR ============================================ // 

	class Blur : public PostProcess
	{
	public:
		Blur(Rendering::FullScreenQuad& fullscreenQuad);
		void Draw(GLuint gameTexture) override;

	private:
		Rendering::Shader shader;
	};

	// ============================================ GAMMA CORECTION ============================================ // 

	class GammaCorection : public PostProcess
	{
	public:
		GammaCorection(Rendering::FullScreenQuad& fullscreenQuad);
		void Draw(GLuint gameTexture) override;

	private:
		Rendering::Shader shader;
	};

}



#endif //POSTPROCESS_HPP