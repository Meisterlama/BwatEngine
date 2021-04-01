#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/RenderableComponent.hpp>
#include <ECS/Components/RigidBodyComponent.hpp>

#include "ResourceManager/ResourceManager.hpp"
#include "ECS/Coordinator.hpp"

#include <Rendering/Model.hpp>

#include "WidgetProperties.hpp"

BwatEngine::Entity WidgetProperties::currentEntity = 0;

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
        const char* modelName = component.model->modelPath.filename().string().c_str();
        ImGui::Text("Mesh");
        ImGui::SameLine();
        if(ImGui::BeginCombo("##Mesh", modelName))
        {
            auto meshList = BwatEngine::ResourceManager::Instance()->GetModelList();

            for(auto &model : meshList)
            {
                bool selected = (modelName == model->modelPath.filename());
                if(ImGui::Selectable(model->modelPath.filename().string().c_str(), selected))
                {
                    component.model = model;
                }
                if(selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        for (int i = 0; i < component.materials.size(); i++)
        {
            const char* DiffName;
            if (component.materials[i]->diffuse != nullptr)
                DiffName = component.materials[i]->diffuse->path.c_str();
            else
                DiffName = "";

            ImGui::Text("Diffuse Texture");
            ImGui::SameLine();
            if(ImGui::BeginCombo("##Diff", DiffName))
            {
                auto textList = BwatEngine::ResourceManager::Instance()->GetTextList();

                for(auto &text : textList)
                {
                    bool selected = (DiffName == text->path);
                    if(ImGui::Selectable(text->path.c_str(), selected))
                    {
                        component.materials[i]->diffuse = text;
                    }
                    if(selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            const char* SpecName;
            if (component.materials[i]->specular != nullptr)
                SpecName = component.materials[i]->specular->path.c_str();
            else
                SpecName = "";

            ImGui::Text("Specular Texture");
            ImGui::SameLine();
            if(ImGui::BeginCombo("##Spec", SpecName))
            {
                auto textList = BwatEngine::ResourceManager::Instance()->GetTextList();

                for(auto &text : textList)
                {
                    bool selected = (SpecName == text->path);
                    if(ImGui::Selectable(text->path.c_str(), selected))
                    {
                        component.materials[i]->specular = text;
                    }
                    if(selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
        }

    }
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::RigidBodyComponent>(BwatEngine::RigidBodyComponent& component)
{
    if (ImGui::CollapsingHeader("RigidBody",ImGuiTreeNodeFlags_DefaultOpen))
    {
        //ImGui::DragFloat3("Velocity", component.velocity.values, 0.01);
        //ImGui::DragFloat3("Acceleration", component.acceleration.values, 0.01);
    }
}

void WidgetProperties::TickVisible()
{
    using namespace BwatEngine;

        Coordinator& coordinator = *Coordinator::GetInstance();
        Signature entitySignature = coordinator.GetEntitySignature(currentEntity);

        if (entitySignature.test(coordinator.GetComponentType<TransformComponent>()))
            ShowComponent(coordinator.GetComponent<TransformComponent>(currentEntity));

        if (entitySignature.test(coordinator.GetComponentType<RenderableComponent>()))
            ShowComponent(coordinator.GetComponent<RenderableComponent>(currentEntity));

        if (entitySignature.test(coordinator.GetComponentType<RigidBodyComponent>()))
            ShowComponent(coordinator.GetComponent<RigidBodyComponent>(currentEntity));
}

void WidgetProperties::Inspect(BwatEngine::Entity& entity)
{
    currentEntity = entity;
}



