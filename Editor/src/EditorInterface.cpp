
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "EditorInterface.hpp"
#include "WidgetMenuBar.hpp"
#include "WidgetHierarchy.hpp"
#include "WidgetAsset.hpp"
#include "WidgetShader.hpp"
#include "WidgetViewport.hpp"
#include "WidgetProperties.hpp"
#include "WidgetPostProcess.hpp"
#include "imgui_internal.h"

#include "Engine.hpp"
#include "ECS/Systems/RenderSystem.hpp"

EditorInterface::EditorInterface(BwatEngine::Engine* _engine)
    : gameViewFramebuffer(_engine->GetWindow().GetWidth(), _engine->GetWindow().GetHeight())
{
    engine = _engine;
    widgets.clear();
    widgets.shrink_to_fit();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

    ImGui_ImplGlfw_InitForOpenGL(engine->GetGLFWwindow(), false);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void EditorInterface::Close()
{
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void EditorInterface::OnTick()
{
    // Render game in editor framebuffer
    GLint previousFramebuffer = gameViewFramebuffer.Bind();
    engine->Update();
    glBindFramebuffer(GL_FRAMEBUFFER, previousFramebuffer);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    BeginWindow();

    for (std::unique_ptr<Widget>& widget : widgets)
    {
        widget->Tick();
    }
    
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //GLFWwindow* backup_current_context = glfwGetCurrentContext();
    //ImGui::UpdatePlatformWindows();
    //ImGui::RenderPlatformWindowsDefault();
    //glfwMakeContextCurrent(backup_current_context);

}

void EditorInterface::Initialise()
{
    ApplyStyle();

    //Push widget here
    widgets.emplace_back(std::make_unique<WidgetMenuBar>(this));
    widgets.emplace_back(std::make_unique<WidgetHierarchy>(this));
    widgets.emplace_back(std::make_unique<WidgetAsset>(this));
    widgets.emplace_back(std::make_unique<WidgetViewport>(this));
    widgets.emplace_back(std::make_unique<WidgetShader>(this));
    widgets.emplace_back(std::make_unique<WidgetPostProcess>(this));

    {
        widgets.emplace_back(std::make_unique<WidgetProperties>(this));
        widgetProperties = static_cast<WidgetProperties*>(widgets.back().get());
    }
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
            ImGui::DockBuilderDockWindow("Assets", dockDownID);
            ImGui::DockBuilderDockWindow("Viewport", dockMainID);
            ImGui::DockBuilderDockWindow("Properties", dockRightID);
            ImGui::DockBuilderDockWindow("Hierarchy", dockRightID);

            ImGui::DockBuilderFinish(dockMainID);
        }

        ImGui::DockSpace(windowID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
    }
}

void EditorInterface::SetEditedEntity(BwatEngine::EntityID entity)
{
    editedEntity = entity;
    widgetProperties->Inspect(editedEntity);
}