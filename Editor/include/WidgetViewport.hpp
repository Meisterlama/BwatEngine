#ifndef BWATENGINE_WIDGETVIEWPORT_HPP
#define BWATENGINE_WIDGETVIEWPORT_HPP

#include "Widget.hpp"
#include "glad/glad.h"
#include "Rendering/FrameBuffer.hpp"
#include "ImGuizmo.h"

class WidgetViewport : public Widget
{
public:
    WidgetViewport(EditorInterface* editor);

    void TickVisible() override;

    ImGuizmo::MODE guizmoMode = ImGuizmo::MODE::WORLD;
    ImGuizmo::OPERATION guizmoOperation = ImGuizmo::OPERATION::TRANSLATE;

private:

    Rendering::FrameBufferObject fbo;
};

#endif //BWATENGINE_WIDGETVIEWPORT_HPP
