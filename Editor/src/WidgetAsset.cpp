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
    if (assetDirectory.loadMe)
    {
        if (ImGui::Button("Load Resources"))
        {
            LoadResources(assetDirectory.loadFile);
            assetDirectory.loadMe = false;
        }
    }

    assetDirectory.ShowList();
}

void WidgetAsset::LoadResources(FileDialog::FileInfoStruct file)
{
    if (file.ext == ".obj" || file.ext == ".fbx")
    {
        BwatEngine::ResourceManager::Instance()->GetOrLoadModel(file.filePath);
    }
    if (file.ext == ".png" || file.ext == ".jpg")
    {
        BwatEngine::ResourceManager::Instance()->GetOrLoadTexture(file.filePath, Rendering::Texture::Type::E_DIFFUSE);
    }
}
