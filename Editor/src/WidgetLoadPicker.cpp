#include "WidgetLoadPicker.hpp"
#include "Serialization/Serialization.hpp"
#include "EditorInterface.hpp"

WidgetLoadPicker::WidgetLoadPicker(EditorInterface *editor) : Widget(editor)
{
    title = "Load Picker";
    flags |= ImGuiWindowFlags_NoScrollbar;

    assetDirectory.OpenDialog("","Assets");
    SetVisible(false);
}

void WidgetLoadPicker::TickVisible()
{
    assetDirectory.ShowList();
    if (ImGui::Button("Load File"))
    {
        if(assetDirectory.SceneLoad(assetDirectory.loadFile))
        {
            SetVisible(false);
            editor->currentScene = assetDirectory.loadFile.filePath.c_str();
        }

    }

}

