#ifndef BWATENGINE_FILEDIALOG_H
#define BWATENGINE_FILEDIALOG_H

#include <filesystem>
#include <set>
#include <vector>

namespace fs = std::filesystem;

class FileDialog
{
public:
    FileDialog();
    void OpenDirectory(fs::path directory);
    void OpenParentDirectory();
    void ScanDirectory();

    void SelectPath(fs::path path);
    void AddSelectedPath(fs::path path);
    void ClearPathSelection();

    void SetFilter(fs::path filter);
    fs::path GetCurrentPath();
    fs::path GetWorkingPath();
    fs::path GetRelativePath(fs::path path);

    void DrawFileList();

    bool BeginFileDialogHeader();
    void EndFileDialogHeader();

    const std::set<fs::path>& GetPathSelection();
    std::set<fs::path> GetDirectoryEntries();

    bool allowMultipleSelection = false;
private:

    bool CheckFilters(fs::path path);

    std::set<fs::path> selectedPaths;
    fs::path currentPath;
    std::string currentPathStr;
    std::set<fs::path> directoryFiles;

    std::string filter;

};
#endif //BWATENGINE_FILEDIALOG_H
