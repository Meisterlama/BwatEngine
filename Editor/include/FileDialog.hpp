#ifndef BWATENGINE_FILEDIALOG_H
#define BWATENGINE_FILEDIALOG_H

#include <filesystem>
#include <set>
#include <vector>

class FileDialog
{
private:
    struct FileInfoStruct
    {
        std::string filePath;
        std::string fileName;
				// I guess it's the file extension ?
				// you could write the full name
				// prioritize readability over practicality
        std::string ext;
    };

    struct FilterInfoStruct
    {
        std::string filter;
        std::set<std::string> collectionFilters;
        
				// define these functions in a .cpp
				void Clear() { filter.clear(); collectionFilters.clear(); }
        bool Empty() const { return filter.empty() && collectionFilters.empty(); }
        bool FilterExist(const std::string& aFilter) { return filter == aFilter || collectionFilters.find(aFilter) != collectionFilters.end(); }
    };

		// you should organize your variables
		// and put some spaces between them
    std::vector<FileInfoStruct> fileList;
    std::vector<FileInfoStruct> filteredFileList;
    std::filesystem::path currentPath;
    std::set<std::string> selectedFileNames;
    std::string name;
    bool showDialog = false;
    std::vector<FilterInfoStruct> filterList;
    FilterInfoStruct selectedFilter;
    std::string dlgFilters{}; // what does dlg mean ?
    std::filesystem::path dlgPath;
    std::filesystem::path dlgDefaultFileName;
    std::filesystem::path dlgDefaultEx;

public:
    FileDialog();
    ~FileDialog(); // rule of three -> https://en.cppreference.com/w/cpp/language/rule_of_three

		// why does your parameters have a prefix ?
		// be consistent with the engine's nomenclature
    void OpenDialog(const char* aFilters, const std::filesystem::path& aFilePathName);
    void ShowList();

protected:	    // set default file name
    void ParseFilters(const char* aFilters);
    void SetSelectedFilterWithExt(const std::string& aFilter);
    void SetPath(const std::string& aPath);
    void ScanDir(const std::string& aPath);
};
#endif //BWATENGINE_FILEDIALOG_H
