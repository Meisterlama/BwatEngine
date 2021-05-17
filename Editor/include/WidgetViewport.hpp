#ifndef BWATENGINE_WIDGETVIEWPORT_HPP
#define BWATENGINE_WIDGETVIEWPORT_HPP

#include "Widget.hpp"
#include "Rendering/FrameBuffer.hpp"
#include "ImGuizmo.h"

class WidgetViewport : public Widget
{
public:
    WidgetViewport(EditorInterface* editor);

    void TickVisible() override;


private:
    Rendering::FrameBufferObject fbo;
};

#endif //BWATENGINE_WIDGETVIEWPORT_HPP
