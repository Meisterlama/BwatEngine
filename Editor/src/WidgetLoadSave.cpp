#include "WidgetLoadSave.hpp"
#include "Serialization/Serialization.hpp"
#include "EditorInterface.hpp"
#include "imgui_stdlib.h"

WidgetLoadSave::WidgetLoadSave(EditorInterface *editor) : Widget(editor)
{
    title = "Load Picker";
    flags |= ImGuiWindowFlags_NoScrollbar;

    fileDialog.SetFilter(".bwat");
    SetVisible(false);
}

void WidgetLoadSave::TickVisible()
{
    fileDialog.DrawFileList();

    if(fileDialog.BeginFileDialogHeader())
    {
        if (saving)
        {
            buttonText = "Save Scene";
            textReadOnly = false;
        }
        else
        {
            buttonText = "Load Scene";
            textReadOnly = true;
        }

        for (auto &path : fileDialog.GetPathSelection())  // Only one path, should be able to remove iterator
        {
            if (is_directory(path))
                continue;

            fileName = path.filename().string();
        }

        if (ImGui::InputText("FileName", &fileName, (textReadOnly) ? ImGuiInputTextFlags_ReadOnly : 0))
        {
            fileDialog.ClearPathSelection();
        }

        ImGui::SameLine();
        if (ImGui::Button(buttonText.c_str()))
        {
            fs::path filePath = (fileDialog.GetCurrentPath() / fileName);
            if (saving)
            {
                BwatEngine::Serialization::SaveScene(filePath.string().c_str());
            }
            else
            {
                BwatEngine::Serialization::LoadScene(filePath.string().c_str());
                editor->currentScene = filePath;
            }

            isVisible = false;
        }
    }
    fileDialog.EndFileDialogHeader();
}
void WidgetLoadSave::Open(bool _saving)
{
    saving = _saving;
    fileDialog.SetFilter(".bwat");
    isVisible = true;
}

