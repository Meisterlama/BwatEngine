#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Math/Math.hpp"

class aiMaterial;

namespace Rendering
{
    class Texture;
	class Shader;

	struct Material
	{
		Material(const aiMaterial& from);
		Material() {}

		Texture* diffuse = nullptr;
		Texture* specular = nullptr;
		Texture* normal = nullptr;

		bool isTextured = false;

		Texture* albedoMap = nullptr;
		Texture* metallicMap = nullptr;
		Texture* roughnessMap = nullptr;
		Texture* aoMap = nullptr;


		BwatEngine::Math::Vec3f albedo;
		float metallic = 0.f;
		float roughness = 0.f;
		float ao = 0.f;

		bool isColor = false;
		BwatEngine::Math::Vec4f color;

		float shininess = 32.f;

		void ApplyToShader(Shader& shader);
		void Bind();

	};
}

#endif // !1
