#ifndef BWATENGINE_WIDGETSHADER_HPP
#define BWATENGINE_WIDGETSHADER_HPP

#include "Widget.hpp"
#include "glad/glad.h"

class EditorInterface;

class WidgetShader : public Widget
{
public:
    WidgetShader(EditorInterface* editor);

    void TickVisible() override;

    void DebugGLBoolText(const char* Name, GLint value, bool color = true);
    void DebugShader(GLuint program, GLuint shader);
    void InspectProgram(GLuint program);
};

#endif //BWATENGINE_WIDGETSHADER_HPP
