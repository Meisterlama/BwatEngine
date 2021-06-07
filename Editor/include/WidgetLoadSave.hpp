#ifndef BWATENGINE_WIDGETLOADPICKER_HPP
#define BWATENGINE_WIDGETLOADPICKER_HPP

#include "Widget.hpp"
#include "FileDialog.hpp"

class WidgetLoadSave : public Widget
{
public:
    WidgetLoadSave(EditorInterface* editor);


    void TickVisible() override;

    void Open(bool saving);

private:
    bool saving = false;
    FileDialog fileDialog;
    std::string fileName;

    std::string buttonText;
    bool textReadOnly;
};

#endif //BWATENGINE_WIDGETLOADPICKER_HPP
