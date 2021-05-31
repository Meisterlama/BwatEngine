#include "Rendering/RenderUI.hpp"


using namespace Rendering;

Render2d::Render2d():shader ({"Assets/Shaders/basic.vs","Assets/Shaders/basic.fs"}) {}

Render2d::Render2d(Quad quad): usedQuad (quad), shader ({"Assets/Shaders/basic.vs","Assets/Shaders/basic.fs"})
{

}

Render2d::~Render2d()
{

}

void Render2d::Draw(GLuint gameTexture)
{
    glBindTexture(GL_TEXTURE_2D, gameTexture);
    shader.Use();
    usedQuad.Draw();
}