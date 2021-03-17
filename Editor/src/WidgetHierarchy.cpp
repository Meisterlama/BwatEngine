#include "WidgetHierarchy.hpp"
#include "WidgetProperties.hpp"
#include "Engine.hpp"
#include "EditorInterface.hpp"

WidgetHierarchy::WidgetHierarchy(EditorInterface *editor) : Widget(editor)
{
    title = "Hierarchy";
    flags |= ImGuiWindowFlags_HorizontalScrollbar;
}

void WidgetHierarchy::TickVisible()
{
    for (BwatEngine::EntityType i = 0; i < editor->engine->entities.size(); i++)
    {
        bool selected = false;
        std::string entityName = (editor->engine->entities[i].name != "") ? editor->engine->entities[i].name :
                                     "Entity_" + std::to_string(editor->engine->entities[i].GetID());
        if (ImGui::TreeNode(entityName.c_str()))
        {
            //if (ImGui::Selectable(entityName.c_str()))
            //{
                WidgetProperties::Inspect(editor->engine->entities[i]);
            //}

            ImGui::TreePop();
        }
    }
}

