#ifndef BWATENGINE_FILEDIALOG_H
#define BWATENGINE_FILEDIALOG_H

#include <filesystem>
#include <set>
#include <vector>

class FileDialog
{
public:
    struct FileInfoStruct
    {
        std::string filePath = "";
        std::string fileName = "";
        std::string ext = "";
    };

    FileDialog();

    void OpenDialog(const char* aFilters, const std::filesystem::path& aFilePathName);
    void ShowList();

    FileInfoStruct loadFile;
    std::filesystem::path currentPath;

private:
    struct FilterInfoStruct
    {
        std::string filter;
        std::set<std::string> collectionFilters;
        void Clear() { filter.clear(); collectionFilters.clear(); }
        bool Empty() const { return filter.empty() && collectionFilters.empty(); }
        bool FilterExist(const std::string& aFilter) { return filter == aFilter || collectionFilters.find(aFilter) != collectionFilters.end(); }
    };

    std::vector<FileInfoStruct> fileList;
    std::vector<FileInfoStruct> filteredFileList;
    std::set<std::string> selectedFileNames;
    std::string name;
    bool showDialog = false;
    std::vector<FilterInfoStruct> filterList;
    FilterInfoStruct selectedFilter;
    std::string dlgFilters{};
    std::filesystem::path dlgPath;
    std::filesystem::path dlgDefaultFileName;
    std::filesystem::path dlgDefaultEx;

protected:
    void ParseFilters(const char* aFilters);
    void SetSelectedFilterWithExt(const std::string& aFilter);
    void SetPath(const std::string& aPath);
    void ScanDir(const std::string& aPath);
    void LoadOnResources(FileInfoStruct file);

    void LoadResources(FileInfoStruct file);
};
#endif //BWATENGINE_FILEDIALOG_H
