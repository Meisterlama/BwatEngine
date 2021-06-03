#include "WidgetHierarchy.hpp"
#include "WidgetProperties.hpp"
#include "Engine.hpp"
#include "EditorInterface.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/DataComponent.hpp"
#include "imgui_internal.h"
#include "ECS/Coordinator.hpp"
#include "Serialization/Serialization.hpp"
#include "WidgetPrefab.hpp"

WidgetHierarchy::WidgetHierarchy(EditorInterface *editor) : Widget(editor)
{
    title = "Hierarchy";
    flags |= ImGuiWindowFlags_HorizontalScrollbar;
}

void WidgetHierarchy::ShowEntity(BwatEngine::EntityID entity)
{
    auto &coordinator = BwatEngine::Coordinator::GetInstance();
    auto &node = coordinator.GetNode(entity);
    std::string entityName;
    if (coordinator.HaveComponent<BwatEngine::DataComponent>(entity))
    {
        entityName = coordinator.GetComponent<BwatEngine::DataComponent>(entity).name;
    }
    else
        entityName = "Entity_" + std::to_string(entity);


    ImGuiTreeNodeFlags flags =
            ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
    if (node.children.empty())
    {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }

    if (entity == editor->GetEditedEntity())
    {
        flags |= ImGuiTreeNodeFlags_Selected;
    }

    bool isOpen = ImGui::TreeNodeEx(entityName.c_str(), flags);

    if (ImGui::BeginPopupContextItem("ShowEntityDeleteContextMenu" ))
    {
        if (ImGui::MenuItem("Delete entity"))
        {
            coordinator.DestroyEntity(entity);
            editor->SetEditedEntity(0);
        }
        if (ImGui::MenuItem("Duplicate entity"))
        {
            using namespace BwatEngine;
            EntityID duplicatedEntity = Serialization::LoadEntity(Serialization::SaveEntity(editor->GetEditedEntity()));
            editor->SetEditedEntity(duplicatedEntity);
        }
        if (ImGui::MenuItem("Save Prefab"))
        {
            using namespace BwatEngine;
            editor->widgetPrefab->Open(true, entity);
        }
        ImGui::EndPopup();
    }

    if (ImGui::IsItemClicked())
    {
        editor->SetEditedEntity(entity);
    }

    if (isOpen)
    {
        for (auto &child : node.children)
        {
            ShowEntity(child->id);
        }
        ImGui::TreePop();
    }
}

void WidgetHierarchy::TickVisible()
{
    auto &coordinator = BwatEngine::Coordinator::GetInstance();

    if (ImGui::BeginPopupContextWindow("CreateEntityContextMenu"))
    {
        if (ImGui::MenuItem("Create entity"))
        {
            coordinator.CreateEntity();
        }
        if (ImGui::MenuItem("Load Prefab"))
        {
            editor->widgetPrefab->Open(false);
        }
        ImGui::EndPopup();
    }

    for (auto &entity : coordinator.GetRootEntities())
    {
        ShowEntity(entity);
    }

}