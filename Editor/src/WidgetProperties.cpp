#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/RenderableComponent.hpp>
#include <ECS/Components/RigidBodyComponent.hpp>


#include <Rendering/Model.hpp>

#include "WidgetProperties.hpp"

BwatEngine::Entity* WidgetProperties::currentEntity = nullptr;

WidgetProperties::WidgetProperties(EditorInterface *editor) : Widget(editor)
{
    title = "Properties";
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::TransformComponent>(BwatEngine::TransformComponent& component)
{
    if (ImGui::CollapsingHeader("Transform",ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::DragFloat3("Position", component.transform.position.values, 0.01);
        ImGui::DragFloat3("Rotation", component.transform.rotation.values, 0.01);
        ImGui::DragFloat3("Scale", component.transform.scale.values, 0.01);
    }
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::RenderableComponent>(BwatEngine::RenderableComponent& component)
{
    if (ImGui::CollapsingHeader("Renderable",ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("Wonderful Model here");
        //ImGui::Text("%s", component.model->directory.c_str());
    }
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::RigidBodyComponent>(BwatEngine::RigidBodyComponent& component)
{
    if (ImGui::CollapsingHeader("RigidBody",ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::DragFloat3("Velocity", component.velocity.values, 0.01);
        ImGui::DragFloat3("Acceleration", component.acceleration.values, 0.01);
    }
}

void WidgetProperties::TickVisible()
{
    using namespace BwatEngine;

    if (currentEntity)
    {
        Signature entitySignature = Entity::GetCoordinator().GetEntitySignature(currentEntity->GetID());

        if (entitySignature.test(Entity::GetComponentType<TransformComponent>()))
            ShowComponent(currentEntity->GetComponent<TransformComponent>());

        if (entitySignature.test(Entity::GetComponentType<RenderableComponent>()))
            ShowComponent(currentEntity->GetComponent<RenderableComponent>());

        if (entitySignature.test(Entity::GetComponentType<RigidBodyComponent>()))
            ShowComponent(currentEntity->GetComponent<RigidBodyComponent>());
    }
}

void WidgetProperties::Inspect(BwatEngine::Entity &entity)
{
    currentEntity = &entity;
}



