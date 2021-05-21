#include "WidgetHierarchy.hpp"
#include "WidgetProperties.hpp"
#include "Engine.hpp"
#include "EditorInterface.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/DataComponent.hpp"
#include "imgui_internal.h"
#include "ECS/Coordinator.hpp"

WidgetHierarchy::WidgetHierarchy(EditorInterface *editor) : Widget(editor)
{
    title = "Hierarchy";
    flags |= ImGuiWindowFlags_HorizontalScrollbar;
}

void WidgetHierarchy::ShowEntity(BwatEngine::EntityID entity)
{
    auto &coordinator = BwatEngine::Coordinator::GetInstance();
    auto &node = coordinator.GetNode(entity);
    std::string entityName = coordinator.GetComponent<BwatEngine::DataComponent>(entity).name;

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
            BwatEngine::Coordinator::GetInstance().DestroyEntity(entity);
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
        ImGui::EndPopup();
    }

    for (auto &entity : coordinator.GetRootEntities())
    {
        ShowEntity(entity);
    }

}