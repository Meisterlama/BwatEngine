#include "WidgetPrefab.hpp"
#include "Serialization/Serialization.hpp"
#include "EditorInterface.hpp"
#include "imgui_stdlib.h"
#include "Math/Common.hpp"

WidgetPrefab::WidgetPrefab(EditorInterface *editor) : Widget(editor)
{
    title = "Prefab Handler";
    flags |= ImGuiWindowFlags_NoScrollbar;

    fileDialog.SetFilter(".prefabwat");
    SetVisible(false);
}

void WidgetPrefab::TickVisible()
{
    fileDialog.DrawFileList();

    if(fileDialog.BeginFileDialogHeader())
    {
        if (saving)
        {
            buttonText = "Save Prefab";
            textReadOnly = false;
        }
        else
        {
            buttonText = "Load Prefab";
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
            if (!filePath.has_extension())
            {
                filePath += ".prefabwat";
            }
            if (saving)
            {
                BwatEngine::Serialization::SavePrefab((selectedEntity != 0) ? selectedEntity : editor->GetEditedEntity(), filePath);
            }
            else
            {
                editor->SetEditedEntity(BwatEngine::Serialization::LoadPrefab(filePath));
            }

            isVisible = false;
        }
    }
    fileDialog.EndFileDialogHeader();
}
void WidgetPrefab::Open(bool _saving, EntityID _selectedEntity)
{
    saving = _saving;
    fileDialog.SetFilter(".prefabwat");
    isVisible = true;
    selectedEntity = _selectedEntity;
}

