#ifndef BWATENGINE_WIDGETMENUBAR_HPP
#define BWATENGINE_WIDGETMENUBAR_HPP

#include "Widget.hpp"

class WidgetMenuBar : public Widget
{
public:
    WidgetMenuBar(EditorInterface* editor);

    void TickAlways() override;
    float GetPadding() { return 8.0f; }

private:
    void MenuFile();
    void MenuOption();
};
#endif //BWATENGINE_WIDGETMENUBAR_HPP
