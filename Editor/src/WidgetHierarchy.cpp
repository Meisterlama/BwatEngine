#include "WidgetHierarchy.hpp"
#include "WidgetProperties.hpp"
#include "Engine.hpp"
#include "EditorInterface.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/DataComponent.hpp"

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
    bool isOpen = ImGui::TreeNodeEx(entityName.c_str(), flags);

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

    for (auto &entity : coordinator.GetRootEntities())
    {
        ShowEntity(entity);
    }
}