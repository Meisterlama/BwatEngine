#include "FileDialog.hpp"
#include "imgui.h"

#if WIN32
#include <direntWin32.h>
#else
#include <dirent.h>
#endif

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
            if (!token.empty() || (token.empty() && pushEmpty)) //-V728
                arr.push_back(token);
            start = end + 1;
            end = text.find(delimiter, start);
        }
        std::string token = text.substr(start);
        if (!token.empty() || (token.empty() && pushEmpty)) //-V728
            arr.push_back(token);
    }
    return arr;
}

FileDialog::FileDialog()
{
    showDialog = false;
}

FileDialog::~FileDialog() = default;

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
    struct dirent** files = nullptr;
    int i = 0;
    int n = 0;
    std::string path = aPath;

    if (!aPath.empty())
    {
        n = scandir(path.c_str(), &files, nullptr, alphasort);
        fileList.clear();

        if (n > 0)
        {
            for (i = 0; i < n; i++)
            {
                struct dirent* ent = files[i];

                FileInfoStruct infos;

                infos.filePath = path;
                infos.fileName = ent->d_name;

                if (infos.fileName != ".")
                {
                    size_t lpt = infos.fileName.find_last_of('.');

                    if (lpt != std::string::npos)
                    {
                        infos.ext = infos.fileName.substr(lpt);
                    }

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

            for (i = 0; i < n; i++)
            {
                free(files[i]);
            }

            free(files);
        }
    }
}

void FileDialog::ShowList()
{
    for (int i = 0; i < fileList.size(); i++)
    {
        if(ImGui::Selectable(fileList[i].fileName.c_str()))
        {
            std::filesystem::path dir = fileList[i].filePath + fileList[i].fileName;
            if (fileList[i].fileName == "..")
                OpenDialog("", dir.parent_path());
            else if (!dir.has_extension())
            {
                OpenDialog("",fileList[i].filePath + "/" + fileList[i].fileName);
            }
        }
    }
}




