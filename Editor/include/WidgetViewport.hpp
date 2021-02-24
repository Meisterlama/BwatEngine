#ifndef BWATENGINE_WIDGETVIEWPORT_HPP
#define BWATENGINE_WIDGETVIEWPORT_HPP

#include "Widget.hpp"

class WidgetViewport : public Widget
{
public:
    WidgetViewport(EditorInterface* editor);

    void TickVisible() override;

private:
    unsigned int fbo;
    unsigned int tex;
    unsigned int rbo;
};

#endif //BWATENGINE_WIDGETVIEWPORT_HPP
