#include "FileDialog.hpp"

#include <utility>
#include "imgui.h"
#include "imgui_stdlib.h"
#include "ResourceManager/ResourceManager.hpp"
#include "Inputs/InputHandler.hpp"

void FileDialog::OpenDirectory(fs::path directory)
{
    if (!is_directory(directory))
        return;
    currentPath = std::move(directory);
    currentPathStr = absolute(currentPath).string();
    selectedPaths.clear();
}
void FileDialog::OpenParentDirectory()
{
    currentPath = absolute(currentPath).parent_path();
    currentPathStr = absolute(currentPath).string();
    selectedPaths.clear();
}

void FileDialog::SelectPath(fs::path path)
{
    ClearPathSelection();
    selectedPaths.insert(path);
}

void FileDialog::AddSelectedPath(fs::path path)
{
    if (allowMultipleSelection)
    {
        selectedPaths.insert(path);
    }
    else
    {
        SelectPath(path);
    }
}

void FileDialog::ClearPathSelection()
{
    selectedPaths.clear();
}

const std::set<fs::path> &FileDialog::GetPathSelection()
{
    return selectedPaths;
}

std::set<fs::path> FileDialog::GetDirectoryEntries()
{
    return directoryFiles;
}

void FileDialog::ScanDirectory()
{
    directoryFiles.clear();

    if (!exists(currentPath))
    {
        ImGui::Text("This directory doesn't exist");
        return;
    }

    for (auto &pathIter : fs::directory_iterator(currentPath))
    {
        if (!CheckFilters(pathIter.path()))
            continue;
        directoryFiles.insert(pathIter.path());
    }
}

#define FILE_ICON(icon_path)                                                                        \
ImGui::Image(reinterpret_cast<ImTextureID>(resMan.GetOrLoadTexture(icon_path)->id), ImVec2(20,20)); \
ImGui::SameLine();


void FileDialog::DrawFileList()
{
    using namespace BwatEngine;
    ResourceManager &resMan = *ResourceManager::Instance();
    ScanDirectory();


    if (BeginFileDialogHeader())
    {
        if (ImGui::Button("^"))
        {
            OpenParentDirectory();
        }
        ImGui::SameLine();
        if (ImGui::InputText("##Current path", &currentPathStr, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            OpenDirectory(currentPathStr);
        }
        ImGui::SameLine();
        ImGui::InputText("##filter", &filter);
    }
    EndFileDialogHeader();

    ImGui::BeginChild("##FILE_LIST");

    for (auto &path : directoryFiles)
    {
        if (is_directory(path))
        {
            FILE_ICON("Assets/image/folder.png")
        }
        else
        {
            FILE_ICON("Assets/image/file.png")
        }
        if (ImGui::Selectable(path.filename().c_str(), selectedPaths.find(path) != selectedPaths.cend()))
        {
            if (InputHandler::GetKeyboard(KEY_LEFT_SHIFT) && !is_directory(path))
            {
                AddSelectedPath(path);
            }
            else
            {
                SelectPath(path);
            }
        }
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
        {
            OpenDirectory(path);
        }
    }
    ImGui::EndChild();
}
FileDialog::FileDialog()
{
    OpenDirectory(fs::current_path());
}
void FileDialog::SetFilter(fs::path _filter)
{
    filter = std::move(_filter);
}
bool FileDialog::CheckFilters(fs::path path)
{
    if (is_directory(path))
        return true;
    if (filter.empty())
        return true;
    if (path.stem().string() == filter)
        return true;
    if (path.extension().string() == filter)
        return true;
    return false;
}
bool FileDialog::BeginFileDialogHeader()
{
    return ImGui::BeginChild("##FILEDIALOG_HEADER", ImVec2(0, 60));
}
void FileDialog::EndFileDialogHeader()
{
    ImGui::EndChild();
}
fs::path FileDialog::GetCurrentPath()
{
    return currentPath;
}
fs::path FileDialog::GetWorkingPath()
{
    return fs::current_path();
}
fs::path FileDialog::GetRelativePath(fs::path path)
{
    return fs::relative(path, GetWorkingPath());
}
