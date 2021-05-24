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


		BwatEngine::Math::Vec3f albedo = {1,1,1};
		float metallic = 0.f;
		float roughness = 0.f;
		float ao = 1.f;

		bool isColor = false;
		BwatEngine::Math::Vec4f color = {0,0,0,1};

		float shininess = 32.f;

		void ApplyToShader(Shader& shader);
		void Bind();

	};
}

#endif // !1
