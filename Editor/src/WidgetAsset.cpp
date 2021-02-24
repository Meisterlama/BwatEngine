#include "../include/WidgetAsset.hpp"

WidgetAsset::WidgetAsset(EditorInterface *editor) : Widget(editor)
{
    title = "Assets";
    flags |= ImGuiWindowFlags_NoScrollbar;
}

void WidgetAsset::TickVisible()
{
    if (ImGui::Button("Import"))
    {

    }
}
