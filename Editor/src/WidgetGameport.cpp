#include "WidgetGameport.hpp"
#include "EditorInterface.hpp"
#include "Engine.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "WidgetProperties.hpp"
#include "Inputs/InputHandler.hpp"
#include "Time.hpp"

WidgetGameport::WidgetGameport(EditorInterface *editor) : Widget(editor)
{
    title = "Gameport";
    flags |= ImGuiWindowFlags_NoScrollbar;
}

void WidgetGameport::TickVisible()
{
    ImGui::GetWindowDrawList()->AddImage(
            (ImTextureID)(size_t)editor->gameViewFramebuffer.textureColor.id, ImVec2(ImGui::GetCursorScreenPos()),
            ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));
}

