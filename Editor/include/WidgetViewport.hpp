#ifndef BWATENGINE_WIDGETVIEWPORT_HPP
#define BWATENGINE_WIDGETVIEWPORT_HPP

#include "Widget.hpp"
#include "glad/glad.h"

class WidgetViewport : public Widget
{
public:
    WidgetViewport(EditorInterface* editor);

    void TickVisible() override;
    GLuint CreateRenderFBO(int width, int height);

private:
    unsigned int fbo;
};

#endif //BWATENGINE_WIDGETVIEWPORT_HPP
