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

    ImGuizmo::MODE guizmoMode = ImGuizmo::MODE::LOCAL;
    ImGuizmo::OPERATION guizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
};

#endif //BWATENGINE_WIDGETVIEWPORT_HPP
