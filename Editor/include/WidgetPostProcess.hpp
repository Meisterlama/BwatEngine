#ifndef WIDGET_POSTPROCESS_HPP
#define WIDGET_POSTPROCESS_HPP

#include "Widget.hpp"
#include "glad/glad.h"

class EditorInterface;

class WidgetPostProcess : public Widget
{
public:
    WidgetPostProcess(EditorInterface* editor);

    void TickVisible() override;

};

#endif // !WIDGET_POSTPROCESS_HPP
