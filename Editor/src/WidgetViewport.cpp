#include "WidgetViewport.hpp"
#include "EditorInterface.hpp"
#include "Engine.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"


WidgetViewport::WidgetViewport(EditorInterface *editor) : Widget(editor) , 
    fbo(editor->engine->GetWindow().GetWidth(), editor->engine->GetWindow().GetHeight())
{
    title = "Viewport";
    flags |= ImGuiWindowFlags_NoScrollbar;

    editor->engine->MainFBO = &fbo;
}

void WidgetViewport::TickVisible()
{
    ImGui::GetWindowDrawList()->AddImage(
            (ImTextureID)(size_t)fbo.textureColor.id, ImVec2(ImGui::GetCursorScreenPos()),
            ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));

    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetDrawlist();
    ImGuizmo::SetRect(0, 0, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

    ImGui::GetItemRectMin();

    auto& coordinator = BwatEngine::Coordinator::GetInstance();
    auto& cameraTransform = coordinator.GetComponent<BwatEngine::TransformComponent>(0);
    auto& cameraComponent = coordinator.GetComponent<BwatEngine::CameraComponent>(0);

    BwatEngine::Math::Mat4f view = BwatEngine::Math::Mat4f::CreateTRSMat(cameraTransform.position, cameraTransform.rotation, cameraTransform.scale).Invert();

    ImGuizmo::Manipulate(view.values, cameraComponent.GetProjectionMatrix().values, guizmoOperation, guizmoMode, BwatEngine::Math::Mat4f::CreateTRSMat(cameraTransform.position, cameraTransform.rotation, cameraTransform.scale).values);
}

