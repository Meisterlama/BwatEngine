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
    void ApplyStyle();

    BwatEngine::Math::Vec4f cText{1};
    BwatEngine::Math::Vec4f cInteractive;
    BwatEngine::Math::Vec4f cIH;
    BwatEngine::Math::Vec4f cBackground;
    BwatEngine::Math::Vec4f cBC;
    BwatEngine::Math::Vec4f cShadow;

    float roundness = 2.0f;
    float jsp = 0.f;
};

#endif // !WIDGET_OPTION_HPP
