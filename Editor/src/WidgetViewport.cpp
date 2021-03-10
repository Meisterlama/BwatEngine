#include "WidgetViewport.hpp"
#include "EditorInterface.hpp"
#include "Engine.hpp"

WidgetViewport::WidgetViewport(EditorInterface *editor) : Widget(editor)
{
    title = "Viewport";
    flags |= ImGuiWindowFlags_NoScrollbar;

    fbo = Rendering::FrameBufferObject(editor->engine->context.window.GetWidth()
                                      ,editor->engine->context.window.GetHeight());

    editor->engine->context.MainFBO = fbo;
}

void WidgetViewport::TickVisible()
{
    ImGui::GetWindowDrawList()->AddImage(
            (ImTextureID)(size_t)fbo.textureColor.id, ImVec2(ImGui::GetCursorScreenPos()),
            ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));
}

