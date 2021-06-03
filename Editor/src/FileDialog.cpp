#include "FileDialog.hpp"
#include "imgui.h"
#include "ResourceManager/ResourceManager.hpp"
#include "Serialization/Serialization.hpp"

inline std::vector<std::string> SplitStringToVector(const std::string& text, char delimiter, bool pushEmpty)
{
    std::vector<std::string> arr;
    if (!text.empty())
    {
        std::string::size_type start = 0;
        std::string::size_type end = text.find(delimiter, start);
        while (end != std::string::npos)
        {
            std::string token = text.substr(start, end - start);
            if (!token.empty() || (token.empty() && pushEmpty))
                arr.push_back(token);
            start = end + 1;
            end = text.find(delimiter, start);
        }
        std::string token = text.substr(start);
        if (!token.empty() || (token.empty() && pushEmpty))
            arr.push_back(token);
    }
    return arr;
}

FileDialog::FileDialog()
{
    showDialog = false;
}

void FileDialog::OpenDialog(const char *aFilters, const std::filesystem::path& aFilePathName)
{
    if (showDialog)
        return;

    if (!aFilePathName.empty())
    {
        dlgPath = aFilePathName;
        dlgDefaultFileName = aFilePathName.filename();
        dlgDefaultEx = aFilePathName.extension();
    }
    else
    {
        dlgPath = ".";
        dlgDefaultFileName = " ";
        dlgDefaultEx.clear();
    }

    ParseFilters(aFilters);
    SetSelectedFilterWithExt(dlgDefaultEx.string());
    SetPath(dlgPath.string());
}

void FileDialog::ParseFilters(const char *aFilters)
{
    fileList.clear();

    if (aFilters)
        dlgFilters = aFilters;
    else
        dlgFilters.clear();

    if (!dlgFilters.empty())
    {
        bool currentFilterFound = false;

        size_t nan = std::string::npos;
        size_t p = 0, lp = 0;

        while((p = dlgFilters.find_first_of("{,", p)) != nan)
        {
            FilterInfoStruct infos;

            if (dlgFilters[p] == '{')
            {
                infos.filter = dlgFilters.substr(lp, p - lp);
                p++;
                lp = dlgFilters.find('}', p);

                if (lp != nan)
                {
                    std::string fs = dlgFilters.substr(p, lp - p);
                    auto arr = SplitStringToVector(fs, ',', false);

                    for (auto a : arr)
                    {
                        infos.collectionFilters.emplace(a);
                    }
                }
                p = lp + 1;
            }
            else
            {
                infos.filter = dlgFilters.substr(lp, p - lp);
                p++;
            }

            if (!currentFilterFound && selectedFilter.filter == infos.filter)
            {
                currentFilterFound = true;
                selectedFilter = infos;
            }

            lp = p;

            if (!infos.Empty())
                filterList.emplace_back(infos);
        }

        std::string token = dlgFilters.substr(lp);

        if (!token.empty())
        {
            FilterInfoStruct infos;
            infos.filter = token;
            filterList.emplace_back(infos);
        }

        if (!currentFilterFound)
            if (!filterList.empty())
                selectedFilter = *filterList.begin();
    }
}

void FileDialog::SetSelectedFilterWithExt(const std::string &aFilter)
{
    if (!filterList.empty())
    {
        if (!aFilter.empty())
        {
            for (const auto& infos : filterList)
            {
                if (aFilter == infos.filter)
                {
                    selectedFilter = infos;
                }
                else
                {
                    for (const auto& filter : infos.collectionFilters)
                    {
                        if (aFilter == filter)
                        {
                            selectedFilter = infos;
                        }
                    }
                }
            }
        }

        if (selectedFilter.Empty())
            selectedFilter = *filterList.begin();
    }
}

void FileDialog::SetPath(const std::string &aPath)
{
    currentPath = aPath;
    fileList.clear();
    if (dlgFilters.empty())
        dlgDefaultFileName = ".";
    ScanDir(currentPath.string());
}

void FileDialog::ScanDir(const std::string &aPath)
{

    std::filesystem::path path = aPath;

    if (!aPath.empty())
    {
        fileList.clear();

        for (auto& p: std::filesystem::directory_iterator(aPath))
        {

            FileInfoStruct infos;

            infos.filePath = p.path().string();
            infos.fileName = p.path().filename().string();

            if (infos.fileName != ".")
            {
                infos.ext = p.path().extension().string();

                if (!dlgFilters.empty())
                {
                    if (!selectedFilter.Empty() &&
                        (!selectedFilter.FilterExist(infos.ext) && selectedFilter.filter != ".*"))
                    {
                        continue;
                    }
                }
            }

            fileList.push_back(infos);
        }
    }
}

void FileDialog::ShowList()
{
    std::filesystem::path dir = currentPath;
    if (ImGui::Button("Back"))
    {
        OpenDialog("", dir.parent_path());
    }

    bool selected = false;

    for (int i = 0; i < fileList.size(); i++)
    {
        ImGui::PushID(fileList[i].fileName.c_str());
        if (fileList[i].fileName == loadFile.fileName)
        {
            selected = true;
        }
        else
            selected = false;

        if (fileList[i].ext == "")
            ImGui::Image(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("EngineAssets/Images/folder.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(20, 20));
        else if (fileList[i].ext == ".jpg" || fileList[i].ext == ".png")
            ImGui::Image(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("EngineAssets/Images/imageFile.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(20, 20));
        else
            ImGui::Image(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("EngineAssets/Images/file.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(20, 20));

        ImGui::SameLine();

        if(ImGui::Selectable(fileList[i].fileName.c_str(), selected))
        {
            if (fileList[i].ext == "")
            {
                OpenDialog("", fileList[i].filePath);
            }
            else
            {
                LoadOnResources(fileList[i]);
            }
        }

        if (isAssetWidget)
        {
            if (ImGui::BeginPopupContextItem("LoadResourceContextMenu"))
            {
                if (ImGui::MenuItem("Load Resources"))
                {
                    LoadOnResources(fileList[i]);
                    LoadResources(fileList[i]);
                }
                ImGui::EndPopup();
            }
        }
        ImGui::PopID();
    }
}

void FileDialog::LoadOnResources(FileInfoStruct file)
{
    loadFile = file;
}

void FileDialog::LoadResources(FileDialog::FileInfoStruct file)
{
    if (file.ext == ".obj" || file.ext == ".fbx")
    {
        BwatEngine::ResourceManager::Instance()->LoadModel(file.filePath);
    }
    else if (file.ext == ".png" || file.ext == ".jpg")
    {
        BwatEngine::ResourceManager::Instance()->GetOrLoadTexture(file.filePath);
    }
    else if (file.ext == ".wav")
    {
        BwatEngine::ResourceManager::Instance()->LoadAudio(file.filePath);
    }
    else
    {
        LogError("[EDITOR] Cannot load unsupported file format.");
    }
}

bool FileDialog::SceneLoad(FileDialog::FileInfoStruct file)
{
    if (file.ext == ".bwat")
    {
        BwatEngine::Serializer::LoadScene(file.filePath.c_str());
        return true;
    }
    else
        return false;
}

