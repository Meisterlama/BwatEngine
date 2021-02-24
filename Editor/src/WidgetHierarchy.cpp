#include "../include/WidgetHierarchy.hpp"

WidgetHierarchy::WidgetHierarchy(EditorInterface *editor) : Widget(editor)
{
    title = "Hierarchy";
    flags |= ImGuiWindowFlags_HorizontalScrollbar;
}

void WidgetHierarchy::TickVisible()
{
    ImGui::Text("Objects");
}

