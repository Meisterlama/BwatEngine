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

    BwatEngine::Math::Vec4f cText = { 0.1f, 0.1f, 0.1f, 1.f };
    BwatEngine::Math::Vec4f cInteractive = { 1, 0.847f, 0, 1 };
    BwatEngine::Math::Vec4f cIH = { 0.714f , 0.714f, 0.714f, 1.f };
    BwatEngine::Math::Vec4f cBackground = { 0.355f, 0.355f, 0.355f, 1.f };
    BwatEngine::Math::Vec4f cBC = { 0.726f, 0.726f, 0.726f, 1.f };
    BwatEngine::Math::Vec4f cShadow = { 0.f, 0.f, 0.f, 0.5f };

    float roundness = 2.0f;
    float jsp = 0.f;
};

#endif // !WIDGET_OPTION_HPP
