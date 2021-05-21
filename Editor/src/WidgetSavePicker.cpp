#include "WidgetSavePicker.hpp"
#include "Serialization/Serialization.hpp"
#include "imgui_stdlib.h"
#include "EditorInterface.hpp"

WidgetSavePicker::WidgetSavePicker(EditorInterface *editor) : Widget(editor)
{
    title = "Save Picker";
    flags |= ImGuiWindowFlags_NoScrollbar;

    assetDirectory.OpenDialog("","Assets");
    SetVisible(false);
}

void WidgetSavePicker::TickVisible()
{
    assetDirectory.ShowList();

    ImGui::InputText("Name", &saveFile);
    ImGui::SameLine();
    std::string path = assetDirectory.currentPath.string() + "/" + saveFile + ".bwat";
    if (ImGui::Button("Save"))
    {
        BwatEngine::Serializer::SaveScene(path.c_str());
        editor->currentScene = path.c_str();
        SetVisible(false);
    }
}

