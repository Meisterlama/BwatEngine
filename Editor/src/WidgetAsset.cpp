#include "WidgetAsset.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Rendering/Texture.hpp"

WidgetAsset::WidgetAsset(EditorInterface *editor) : Widget(editor)
{
    title = "Assets";
    flags |= ImGuiWindowFlags_NoScrollbar;

    assetDirectory.OpenDialog("","Assets");
}

void WidgetAsset::TickVisible()
{
    assetDirectory.ShowList();
}