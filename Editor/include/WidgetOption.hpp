#ifndef WIDGET_OPTION_HPP
#define WIDGET_OPTION_HPP

#include "Widget.hpp"
#include "glad/glad.h"
#include "Math/Math.hpp"

class EditorInterface;

class WidgetOption : public Widget
{
public:
    WidgetOption(EditorInterface* editor);

    void TickVisible() override;
    void CubeMapEditing();
};

#endif // !WIDGET_OPTION_HPP
