#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../include/EditorInterface.hpp"
#include "../include/WidgetMenuBar.hpp"
#include "../include/WidgetHierarchy.hpp"
#include "../include/WidgetAsset.hpp"
#include "../../lib/imgui/include/imgui_internal.h"

EditorInterface::~EditorInterface()
{
    widgets.clear();
    widgets.shrink_to_fit();
}

void EditorInterface::DestroyImGui()
{
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void EditorInterface::OnTick()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    BeginWindow();

    for (std::shared_ptr<Widget>& widget : widgets)
    {
        widget->Tick();
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
}

void EditorInterface::Initialise(Bwat::Window mainWindow)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    ApplyStyle();

    ImGui_ImplGlfw_InitForOpenGL(mainWindow.window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    //Push widget here
    widgets.emplace_back(std::make_shared<WidgetMenuBar>(this));
    widgets.emplace_back(std::make_shared<WidgetHierarchy>(this));
    widgets.emplace_back(std::make_shared<WidgetAsset>(this));
}

void EditorInterface::ApplyStyle() const
{
    //Future BWAT style here
}

void EditorInterface::BeginWindow()
{
    const auto windowFlags =    ImGuiWindowFlags_MenuBar                |
                                ImGuiWindowFlags_NoTitleBar             |
                                ImGuiWindowFlags_NoDocking              |
                                ImGuiWindowFlags_NoCollapse             |
                                ImGuiWindowFlags_NoResize               |
                                ImGuiWindowFlags_NoMove                 |
                                ImGuiWindowFlags_NoBringToFrontOnFocus  |
                                ImGuiWindowFlags_NoNavFocus;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y));
    ImGui::SetNextWindowViewport(viewport->ID);

    bool open = true;
    editorBegun = ImGui::Begin("Bwat Engine", &open, windowFlags);

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable && editorBegun)
    {
        //Dock space
        const auto windowID = ImGui::GetID("Bwat Engine");

        if (!ImGui::DockBuilderGetNode(windowID))
        {
            ImGui::DockBuilderRemoveNode(windowID);
            ImGui::DockBuilderAddNode(windowID, ImGuiDockNodeFlags_None);
            ImGui::DockBuilderSetNodeSize(windowID, ImGui::GetMainViewport()->Size);

            ImGuiID dockMainID = windowID;
            ImGuiID dockRightID = ImGui::DockBuilderSplitNode(dockMainID, ImGuiDir_Right, 0.2f, nullptr, &dockMainID);
            ImGuiID dockDownID = ImGui::DockBuilderSplitNode(dockMainID, ImGuiDir_Down, 0.25f, nullptr, &dockMainID);

            //Docks widgets here
            ImGui::DockBuilderDockWindow("Hierarchy", dockRightID);
            ImGui::DockBuilderDockWindow("Assets", dockDownID);

            ImGui::DockBuilderFinish(dockMainID);
        }

        ImGui::DockSpace(windowID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
    }
}





















/*EditorInterface::EditorInterface()
{
    glGenFramebuffers(1, &fbo);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

}

void EditorInterface::ShowScene(float color[3])
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    glClearColor(color[0], color[1], color[2], 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //BwatEngine.Render();
    glClearColor(color[0], color[1], color[2], 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ImGui::Begin("Scene Window");

    ImGui::GetWindowDrawList()->AddImage(
            (void *)tex, ImVec2(ImGui::GetCursorScreenPos()),
            ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
}

void EditorInterface::DrawInterface(float color[3])
{
    ImGui::Begin("Color");
    ImGui::ColorEdit3("Clear color", color);
    ImGui::End();

    ImGui::Begin("Project");
    ImGui::Text("First Project");
    ImGui::End();

    ImGui::Begin("Inspector");
    ImGui::Text("Transform of object");
    ImGui::End();

    ShowScene(color);

    RenderImGui();
}*/
