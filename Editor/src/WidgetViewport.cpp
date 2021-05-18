#include "WidgetViewport.hpp"
#include "EditorInterface.hpp"
#include "Engine.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "WidgetProperties.hpp"

WidgetViewport::WidgetViewport(EditorInterface *editor) : Widget(editor)
{
    title = "Viewport";
    flags |= ImGuiWindowFlags_NoScrollbar;
}

void WidgetViewport::TickVisible()
{
    ImGui::GetWindowDrawList()->AddImage(
            (ImTextureID)(size_t)editor->gameViewFramebuffer.textureColor.id, ImVec2(ImGui::GetCursorScreenPos()),
            ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));

    if (editor->engine->isPlaying == false)
    {
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

        auto& coordinator = BwatEngine::Coordinator::GetInstance();
        BwatEngine::Signature signature;
        signature.set(coordinator.GetComponentType<BwatEngine::CameraComponent>());
        auto cameras = coordinator.GetEntitiesWithSignature(signature);

        auto& cameraTransform = coordinator.GetComponent<BwatEngine::TransformComponent>(cameras[0]);
        auto& cameraComponent = coordinator.GetComponent<BwatEngine::CameraComponent>(cameras[0]);
        BwatEngine::Math::Mat4f view = BwatEngine::Math::Mat4f::CreateTRSMat(cameraTransform.position, cameraTransform.rotation, cameraTransform.scale).Invert();

        BwatEngine::EntityID entity = editor->GetEditedEntity();
        if (coordinator.HaveComponent<BwatEngine::TransformComponent>(entity))
        {
            auto& entityTransform = coordinator.GetComponent<BwatEngine::TransformComponent>(entity);

            BwatEngine::Math::Vec3f& eulerAngles = editor->widgetProperties->eulersInDegrees;
            BwatEngine::Math::Mat4f entityMat;
            ImGuizmo::RecomposeMatrixFromComponents(
                    entityTransform.position.values,
                    eulerAngles.values,
                    entityTransform.scale.values,
                    entityMat.values);

            BwatEngine::Math::Mat4f proj = cameraComponent.GetProjectionMatrix();

            if (ImGuizmo::Manipulate(view.values, proj.values, EditorInterface::guizmoOperation, EditorInterface::guizmoMode, entityMat.values))
            {
                BwatEngine::Math::Vec3f pos;
                BwatEngine::Math::Vec3f sca;
                ImGuizmo::DecomposeMatrixToComponents(
                        entityMat.values,
                        pos.values,
                        eulerAngles.values,
                        sca.values
                );

                switch (EditorInterface::guizmoOperation)
                {
                    case ImGuizmo::OPERATION::TRANSLATE:
                        entityTransform.position = pos;
                        break;

                    case ImGuizmo::OPERATION::ROTATE:
                    {
                        BwatEngine::Math::Vec3f radEulers;
                        radEulers.X = BwatEngine::Math::ToRads(eulerAngles.X);
                        radEulers.Y = BwatEngine::Math::ToRads(eulerAngles.Y);
                        radEulers.Z = BwatEngine::Math::ToRads(eulerAngles.Z);
                        entityTransform.rotation = BwatEngine::Math::Quatf(radEulers);
                    }
                        break;

                    case ImGuizmo::OPERATION::SCALE:
                        entityTransform.scale = sca;
                }
            }
        }
    }
}

