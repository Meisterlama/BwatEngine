#ifndef BWATENGINE_WIDGETTOOLS_HPP
#define BWATENGINE_WIDGETTOOLS_HPP

#include "Widget.hpp"
#include "ImGuizmo.h"

class WidgetTools: public Widget
{
public:
    WidgetTools(EditorInterface* editor);

    void TickVisible() override;

    static ImGuizmo::MODE guizmoMode;
    static ImGuizmo::OPERATION guizmoOperation;
};

#endif //BWATENGINE_WIDGETTOOLS_HPP
