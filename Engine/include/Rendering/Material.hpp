#ifndef MATERIAL_HPP
#define MATERIAL_HPP

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

		//BwatEngine::Math::Vec3f color;

		void Bind();
		void SetDiffuse(Texture& texture);

	};
}

#endif // !1
