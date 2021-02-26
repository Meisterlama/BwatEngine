#include "WidgetViewport.hpp"
#include "glad/glad.h"

WidgetViewport::WidgetViewport(EditorInterface *editor) : Widget(editor)
{
    title = "Viewport";
    flags |= ImGuiWindowFlags_NoScrollbar;

    fbo = CreateRenderFBO(800, 600);
}

void WidgetViewport::TickVisible()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glClearColor(0.f, 0.4f, 0.6f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    //render.RenderScene();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ImGui::GetWindowDrawList()->AddImage(
            (ImTextureID)(size_t)fbo, ImVec2(ImGui::GetCursorScreenPos()),
            ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));
}

GLuint WidgetViewport::CreateRenderFBO(int width, int height)
{
    GLuint colorTexture = 0;
    GLuint depthRenderbuffer = 0;

    {
        glGenTextures(1, &colorTexture);
        glBindTexture(GL_TEXTURE_2D, colorTexture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // Create depth buffer
    {
        glGenRenderbuffers(1, &depthRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);

    GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    assert(status == GL_FRAMEBUFFER_COMPLETE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return fbo;
}

