#include "WidgetHierarchy.hpp"
#include "WidgetProperties.hpp"
#include "Engine.hpp"

WidgetHierarchy::WidgetHierarchy(EditorInterface *editor) : Widget(editor)
{
    title = "Hierarchy";
    flags |= ImGuiWindowFlags_HorizontalScrollbar;
}

void WidgetHierarchy::TickVisible()
{
    ImGui::Text("Objects");

    ImGui::ListBoxHeader("Entities");
    for (EntityType i = 0; i < entities.size(); i++)
    {
        bool selected = false;
        std::string entityName = (entities[i].name != "")?entities[i].name  : "Entity_" + std::to_string(entities[i].GetID());

        if (ImGui::Selectable(entityName.c_str()))
        {
            WidgetProperties::Inspect(entities[i]);
        }
    }
    ImGui::ListBoxFooter();
}

