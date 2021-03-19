#include "FileDialog.hpp"

FileDialog::FileDialog()
{
    showDialog = false;
}

FileDialog::~FileDialog() = default;

void FileDialog::OpenDialog(const char *aFilters, const std::filesystem::path& aFilePathName,ImGuiFileDialogFlags flags)
{
    if (showDialog)
        return;
}

