#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Texture.hpp"
//#include "Math/Math.hpp"

class aiMaterial;

namespace Rendering
{
	struct Material
	{
		Material(const aiMaterial& from);
		Material() {}

		Texture* diffuse = nullptr;
		Texture* specular = nullptr;
		Texture* normal = nullptr;

		float shininess = 32.f;
		//BwatEngine::Math::Vec3f color;

		void Bind();
		void SetDiffuse(Texture& texture);

	};
}

#endif // !1
