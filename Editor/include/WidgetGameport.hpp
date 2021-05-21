#ifndef BWATENGINE_WIDGETGAMEPORT_HPP
#define BWATENGINE_WIDGETGAMEPORT_HPP

#include "Widget.hpp"
#include "Rendering/FrameBuffer.hpp"
#include "ImGuizmo.h"

class WidgetGameport : public Widget
{
public:
    WidgetGameport(EditorInterface* editor);

    void TickVisible() override;

private:
    Rendering::FrameBufferObject fbo;
};

#endif //BWATENGINE_WIDGETGAMEPORT_HPP
