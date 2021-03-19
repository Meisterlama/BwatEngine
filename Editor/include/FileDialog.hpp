#ifndef BWATENGINE_FILEDIALOG_H
#define BWATENGINE_FILEDIALOG_H

class FileDialog
{
private:
    struct FileInfoStruct
    {
        char type = '';
        std::filesystem::path filePath;
        std::string fileName;
        std::string ext;
    };

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
    std::filesystem::path currentPath;
    std::set<std::string> selectedFileNames;
    std::string name;
    bool showDialog = false;
    std::vector<FilterInfoStruct> filterList;
    FilterInfoStruct selectedFilter;

public:
    FileDialog();
    ~FileDialog();

    void OpenDialog(const char* aFilters, const std::filesystem::path& aFilePathName, ImGuiFileDialogFlags flags = 0);

protected:
    void SetDefaultFileName(const std::string& aFileName);																// set default file name
    bool SelectDirectory(const FileInfoStruct& aInfos);																	// enter directory
    void SelectFileName(const FileInfoStruct& aInfos);
};
#endif //BWATENGINE_FILEDIALOG_H
