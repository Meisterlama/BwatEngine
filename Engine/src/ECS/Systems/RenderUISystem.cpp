#include "ECS/Systems/RenderUISystem.hpp"
#include "ResourceManager/ResourceManager.hpp"

using namespace BwatEngine;

RenderUISystem::RenderUISystem(int width, int height)
{
    framebuffer.Resize(width, height);
    render.usedQuad = quad;
    text = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/red.png");

}

void RenderUISystem::Begin()
{
    framebuffer.Bind();
}
void RenderUISystem::Update()
{
    render.Draw(text->id);
}