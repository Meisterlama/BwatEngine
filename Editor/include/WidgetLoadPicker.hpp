#ifndef BWATENGINE_WIDGETLOADPICKER_HPP
#define BWATENGINE_WIDGETLOADPICKER_HPP

#include "Widget.hpp"
#include "FileDialog.hpp"

class WidgetLoadPicker : public Widget
{
public:
    WidgetLoadPicker(EditorInterface* editor);

    FileDialog assetDirectory;
    std::string saveFile;

    void TickVisible() override;
};

#endif //BWATENGINE_WIDGETLOADPICKER_HPP
