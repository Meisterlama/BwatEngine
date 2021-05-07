#include "WidgetTools.hpp"
#include "ResourceManager/ResourceManager.hpp"

ImGuizmo::MODE WidgetTools::guizmoMode = ImGuizmo::MODE::LOCAL;
ImGuizmo::OPERATION WidgetTools::guizmoOperation = ImGuizmo::OPERATION::TRANSLATE;

WidgetTools::WidgetTools(EditorInterface* editor) : Widget(editor)
{
    title = "Tools";
    flags |= ImGuiWindowFlags_NoScrollbar;
}

void WidgetTools::TickVisible()
{
    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/trans.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(25.f, 25.f)))
    {
        guizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/rotate.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(25.f, 25.f)))
    {
        guizmoOperation = ImGuizmo::OPERATION::ROTATE;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/scale.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(25.f, 25.f)))
    {
        guizmoOperation = ImGuizmo::OPERATION::SCALE;
    }

    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 125);
    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/world.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(25.f, 25.f)))
    {
        guizmoMode = ImGuizmo::MODE::WORLD;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/local.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(25.f, 25.f)))
    {
        guizmoMode = ImGuizmo::MODE::LOCAL;
    }
}

