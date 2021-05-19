#ifndef BWATENGINE_WIDGETSAVEPICKER_HPP
#define BWATENGINE_WIDGETSAVEPICKER_HPP

#include "Widget.hpp"
#include "FileDialog.hpp"

class WidgetSavePicker : public Widget
{
public:
    WidgetSavePicker(EditorInterface* editor);

    FileDialog assetDirectory;
    std::string saveFile;

    void TickVisible() override;
};

#endif //BWATENGINE_WIDGETSAVEPICKER_HPP
