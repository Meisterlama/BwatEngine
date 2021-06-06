#include "WidgetAsset.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Rendering/Texture.hpp"

WidgetAsset::WidgetAsset(EditorInterface *editor) : Widget(editor)
{
    title = "Assets";
    flags |= ImGuiWindowFlags_NoScrollbar;
    fileDialog.allowMultipleSelection = true;
}

void WidgetAsset::TickVisible()
{
    fileDialog.DrawFileList();

    if(fileDialog.BeginFileDialogHeader())
    {
        if(ImGui::Button("Load Selected Assets"))
        {
            for (auto& path : fileDialog.GetPathSelection())
            {
                if (is_directory(path))
                    continue;

                fs::path ext = path.extension();
                fs::path relPath = fileDialog.GetRelativePath(path);

                if (ext == ".obj" || ext == ".fbx")
                {
                    BwatEngine::ResourceManager::Instance()->LoadModel(relPath);
                }
                else if (ext == ".png" || ext == ".jpg")
                {
                    BwatEngine::ResourceManager::Instance()->GetOrLoadTexture(relPath);
                }
                else if (ext == ".wav")
                {
                    BwatEngine::ResourceManager::Instance()->LoadAudio(relPath);
                }
                else if (ext == ".lua")
                {
                    BwatEngine::ResourceManager::Instance()->LoadScript(relPath);
                }
            }
        }
    }
    fileDialog.EndFileDialogHeader();
}