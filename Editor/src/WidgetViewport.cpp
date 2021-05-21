#include "WidgetViewport.hpp"
#include "EditorInterface.hpp"
#include "Engine.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "WidgetProperties.hpp"
#include "Inputs/InputHandler.hpp"
#include "Time.hpp"

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

    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetDrawlist();
    ImGuizmo::SetRect(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

    auto& coordinator = BwatEngine::Coordinator::GetInstance();

    auto& cameraTransform = editor->cameraTransform;
    auto& cameraComponent = editor->camera;
    cameraComponent.aspect = ImGui::GetWindowWidth() / ImGui::GetWindowHeight();
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
    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
    {
        BwatEngine::InputHandler::SetMouseStatus(BwatEngine::Disabled);
        ImGui::SetWindowFocus();
        editor->cursorLocked = true;
    }
    if (editor->cursorLocked && !BwatEngine::InputHandler::GetMouseButton(BwatEngine::MOUSE_BUTTON_2))
    {
        BwatEngine::InputHandler::SetMouseStatus(BwatEngine::Normal);
        editor->cursorLocked = false;
    }
    if (editor->cursorLocked)
    {
        HandleCamera();
    }
}

void WidgetViewport::HandleCamera()
{
    using namespace BwatEngine;
    Math::Vec2f mouseDelta = InputHandler::GetMouseDelta();
    float sensitivity_mouse = -0.1f;
    mouseDelta *= sensitivity_mouse * Time::deltaTime;

    editor->rotation.X = Math::Clamp(editor->rotation.X + mouseDelta.Y, - Math::PI / 2, Math::PI / 2);
    editor->rotation.Y = Math::Loop(editor->rotation.Y + mouseDelta.X, 0, Math::PI * 2);

    editor->cameraTransform.rotation = {editor->rotation};

    float Speed = 25.f;
    float FrameSpeed = Speed * Time::deltaTime;


    if (InputHandler::GetKeyboard(KEY_LEFT_SHIFT))
        FrameSpeed *= 5.f;


    float ForwardVelocity = 0.f;
    if (InputHandler::GetKeyboard(KEY_W))
        ForwardVelocity = -FrameSpeed;
    if (InputHandler::GetKeyboard(KEY_S))
        ForwardVelocity = FrameSpeed;


    float StrafeVelocity = 0.f;
    if (InputHandler::GetKeyboard(KEY_A))
        StrafeVelocity = -FrameSpeed;
    if (InputHandler::GetKeyboard(KEY_D))
        StrafeVelocity = FrameSpeed;

    if (InputHandler::GetKeyboard(KEY_Q) | InputHandler::GetKeyboard(KEY_SPACE))
        editor->cameraTransform.position.Y += Speed * Time::deltaTime;

    if (InputHandler::GetKeyboard(KEY_Z) | InputHandler::GetKeyboard(KEY_LEFT_CONTROL))
        editor->cameraTransform.position.Y -= Speed * Time::deltaTime;

    Math::Vec3f forwardVec = editor->cameraTransform.rotation.Rotate({0, 0, 1}).Normalize();
    Math::Vec3f rightVec = editor->cameraTransform.rotation.Rotate({1, 0, 0}).Normalize();
    Math::Vec3f upVec = editor->cameraTransform.rotation.Rotate({0, 1, 0}).Normalize();

    Math::Vec3f translation = forwardVec * ForwardVelocity + rightVec * StrafeVelocity;

    editor->cameraTransform.position += translation;

    float orientation[6] = {
            -forwardVec.X,
            -forwardVec.Y,
            -forwardVec.Z,
            upVec.X,
            upVec.Y,
            upVec.Z,
    };

    alListenerfv(AL_POSITION, editor->cameraTransform.position.values);
    alListenerfv(AL_ORIENTATION, orientation);
}

