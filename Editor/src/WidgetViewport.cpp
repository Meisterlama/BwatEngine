#include "WidgetViewport.hpp"
#include "EditorInterface.hpp"
#include "Engine.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "WidgetProperties.hpp"
#include "ResourceManager/ResourceManager.hpp"

WidgetViewport::WidgetViewport(EditorInterface *editor) : Widget(editor) , 
    fbo(editor->engine->GetWindow().GetWidth(), editor->engine->GetWindow().GetHeight())
{
    title = "Viewport";
    flags |= ImGuiWindowFlags_NoScrollbar;

    editor->engine->MainFBO = &fbo;
}

void WidgetViewport::TickVisible()
{
    if (ImGui::ImageButton((ImTextureID)BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/trans.png",Rendering::Texture::Type::E_DIFFUSE)->id, ImVec2(50.f, 50.f)))
    {
        guizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton((ImTextureID)BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/Rotate.png",Rendering::Texture::Type::E_DIFFUSE)->id, ImVec2(50.f, 50.f)))
    {
        guizmoOperation = ImGuizmo::OPERATION::ROTATE;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton((ImTextureID)BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/scale.png",Rendering::Texture::Type::E_DIFFUSE)->id, ImVec2(50.f, 50.f)))
    {
        guizmoOperation= ImGuizmo::OPERATION::SCALE;
    }

    ImGui::GetWindowDrawList()->AddImage(
            (ImTextureID)(size_t)fbo.textureColor.id, ImVec2(ImGui::GetCursorScreenPos()),
            ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));

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

    if (coordinator.HaveComponent<BwatEngine::TransformComponent>(WidgetProperties::currentEntity))
    {
        auto& entityTransform = coordinator.GetComponent<BwatEngine::TransformComponent>(WidgetProperties::currentEntity);
        BwatEngine::Math::Mat4f entityMat = BwatEngine::Math::Mat4f::CreateTRSMat(entityTransform.position, entityTransform.rotation, entityTransform.scale);
        BwatEngine::Math::Mat4f proj = cameraComponent.GetProjectionMatrix();

        ImGuizmo::Manipulate(view.values, proj.values, guizmoOperation, guizmoMode, entityMat.values);

        if(ImGuizmo::IsUsing())
        {
            BwatEngine::Math::Vec3f pos;
            BwatEngine::Math::Quatf rot;
            BwatEngine::Math::Vec3f sca;

            entityMat.DecomposeTransform(pos, rot, sca);

            switch (guizmoOperation)
            {
                case ImGuizmo::OPERATION::TRANSLATE:
                    entityTransform.position = pos;
                    break;

                case ImGuizmo::OPERATION::ROTATE:
                    entityTransform.rotation = rot;
                    break;

                case ImGuizmo::OPERATION::SCALE:
                    entityTransform.scale = sca;
            }
        }
    }
}

