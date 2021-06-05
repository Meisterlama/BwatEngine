#include "Rendering/RenderUI.hpp"
#include "Math/Math.hpp"


using namespace Rendering;
using namespace BwatEngine::Math;



void Image2D::SetImagePos(const BwatEngine::Math::Vec2f& pos)
{
    position.X = pos.X;
    position.Y = pos.Y;
}

void Image2D::SetImageScale(const BwatEngine::Math::Vec2f& value)
{
    scale.X = value.X;
    scale.Y = value.Y;
}

void Image2D::SetImageRotation(float value)
{
    rotation = value * PI / 180;
}

void Image2D::SetIsActive(bool value)
{
    isActive = value;
}



Render2d::Render2d():shader ({"Assets/Shaders/UIRender.vs","Assets/Shaders/UIRender.fs"}) {}

Render2d::Render2d(Quad quad): usedQuad (quad), shader ({"Assets/Shaders/UIRender.vs","Assets/Shaders/UIRender.fs"})
{

}

Render2d::~Render2d()
{
    for (auto& image : images)
        delete image;
}

void Render2d::Draw(Mat4f view, Mat4f proj)
{
    for (auto& imagesIt : images)
    {
        if (imagesIt->isActive)
        {

            GLuint gameTextures = imagesIt->tex->id;
            glBindTexture(GL_TEXTURE_2D, gameTextures);
            shader.Use();

            Mat4f model = Mat4f::CreateTRSMat(Vec3f {imagesIt->position.X, imagesIt->position.Y, -0.1f},
                                              Vec3f{0.f, 0.f, imagesIt->rotation},
                                              Vec3f{imagesIt->scale.X, imagesIt->scale.Y, 1.f}
                                              );

            shader.SetMat4("model", model);
            shader.SetMat4("view", view);
            shader.SetMat4("projection", proj);
            usedQuad.Draw();
        }

    }

}