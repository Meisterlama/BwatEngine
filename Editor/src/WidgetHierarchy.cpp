#include "WidgetHierarchy.hpp"
#include "WidgetProperties.hpp"
#include "Engine.hpp"
#include "EditorInterface.hpp"

#include "ECS/Coordinator.hpp"

WidgetHierarchy::WidgetHierarchy(EditorInterface *editor) : Widget(editor)
{
    title = "Hierarchy";
    flags |= ImGuiWindowFlags_HorizontalScrollbar;
}

void ShowEntity(BwatEngine::Entity entity)
{
    auto &coordinator = *BwatEngine::Coordinator::GetInstance();
    auto &node = coordinator.GetNode(entity);
    std::string entityName = "Entity_" + std::to_string(entity);

    ImGuiTreeNodeFlags flags =
            ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
    if (node.children.empty())
    {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }
    bool isOpen = ImGui::TreeNodeEx(entityName.c_str(), flags);

    if (ImGui::IsItemClicked())
    {
        WidgetProperties::Inspect(entity);
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
    auto &coordinator = *BwatEngine::Coordinator::GetInstance();

    for (auto &entity : coordinator.GetRootEntities())
    {
        ShowEntity(entity);
    }
}