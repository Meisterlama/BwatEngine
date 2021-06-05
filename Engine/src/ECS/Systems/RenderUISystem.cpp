#include "ECS/Systems/RenderUISystem.hpp"
#include "ResourceManager/ResourceManager.hpp"


using namespace BwatEngine;

RenderUISystem::RenderUISystem()
{
    Rendering::Image2D* image = CreateImage("Assets/image/moteur.jpg");


    image->SetImagePos({200,100});



}

void RenderUISystem::Update()
{
    glDisable(GL_DEPTH_TEST);
    render.Draw(view, proj);
    glEnable(GL_DEPTH_TEST);

}

Rendering::Image2D* RenderUISystem::CreateImage(const char* textPath)
{
    Rendering::Image2D* image = new Rendering::Image2D();
    image->tex = ResourceManager::Instance()->GetOrLoadTexture(textPath);
    image->isActive = true;
    render.images.push_back(image);


    return image;
}
void RenderUISystem::SetCamMatrix(CameraComponent &camComp, TransformComponent &camTransform)
{

    view = Math::Mat4f::CreateTRSMat({0.f, 0.f, 0.f}, {0.f, 0.f, 0.f, 1.f}, {1.f, 1.f, 1.f});
    proj = Math::Mat4f::CreateOrtho(600.0f, -600.0f, -360.0f, 360.0f, camComp.near, camComp.far);
}
