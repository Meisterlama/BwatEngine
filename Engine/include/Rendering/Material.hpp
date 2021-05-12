#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Math/Math.hpp"

class aiMaterial;

namespace Rendering
{
    class Texture;
	struct Material
	{
		Material(const aiMaterial& from);
		Material() {}

		Texture* diffuse = nullptr;
		Texture* specular = nullptr;
		Texture* normal = nullptr;

		bool isColor = false;
		BwatEngine::Math::Vec4f color;

		float shininess = 32.f;

		void Bind();
		void SetDiffuse(Texture& texture);

	};
}

#endif // !1
