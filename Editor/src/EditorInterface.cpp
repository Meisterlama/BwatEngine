
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "EditorInterface.hpp"
#include "WidgetMenuBar.hpp"
#include "WidgetHierarchy.hpp"
#include "WidgetAsset.hpp"
#include "WidgetViewport.hpp"
#include "WidgetProperties.hpp"
#include "WidgetTools.hpp"
#include "imgui_internal.h"

#include "Engine.hpp"

EditorInterface::EditorInterface(BwatEngine::Engine* _engine)
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

    widgets.emplace_back(std::make_unique<WidgetProperties>(this));
    widgetProperties = static_cast<WidgetProperties*>(widgets.back().get());

    widgets.emplace_back(std::make_unique<WidgetTools>(this));
}

void EditorInterface::ApplyStyle() const
{
    // Color settings
    const auto color_text                   = ImVec4(50.f  / 255.f, 50.f  / 255.f, 50.f  / 255.f, 1.f);
    const auto color_text_disabled          = ImVec4(color_text.x, color_text.y, color_text.z, 0.5f);
    const auto color_interactive            = ImVec4(1.f, 1.f, 185.f/255.f, 1.f);
    const auto color_interactive_hovered    = ImVec4(1.f, 215.f/255.f, 100.f/255.f, 1.f);
    const auto color_interactive_clicked    = ImVec4(1.f, 1.f, 124.f/255.f, 1.f);
    const auto color_background             = ImVec4(150.f  / 255.f, 150.f  / 255.f, 150.f  / 255.f, 1.f);
    const auto color_background_content     = ImVec4(100.f  / 255.f, 100.f  / 255.f, 100.f  / 255.f, 1.f);
    const auto color_shadow                 = ImVec4(0.f, 0.f, 0.f, 0.5f);

    // Colors
    ImVec4* colors                          = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = color_text;
    colors[ImGuiCol_TextDisabled]           = color_text_disabled;
    colors[ImGuiCol_WindowBg]               = color_background;             // Background of normal windows
    colors[ImGuiCol_ChildBg]                = color_background;             // Background of child windows
    colors[ImGuiCol_PopupBg]                = color_background;             // Background of popups, menus, tooltips windows
    colors[ImGuiCol_Border]                 = color_interactive;
    colors[ImGuiCol_BorderShadow]           = color_shadow;
    colors[ImGuiCol_FrameBg]                = color_background_content;     // Background of checkbox, radio button, plot, slider, text input
    colors[ImGuiCol_FrameBgHovered]         = color_interactive;
    colors[ImGuiCol_FrameBgActive]          = color_interactive_clicked;
    colors[ImGuiCol_TitleBg]                = color_background_content;
    colors[ImGuiCol_TitleBgActive]          = color_interactive;
    colors[ImGuiCol_TitleBgCollapsed]       = color_background;
    colors[ImGuiCol_MenuBarBg]              = color_background_content;
    colors[ImGuiCol_ScrollbarBg]            = color_background_content;
    colors[ImGuiCol_ScrollbarGrab]          = color_interactive;
    colors[ImGuiCol_ScrollbarGrabHovered]   = color_interactive_hovered;
    colors[ImGuiCol_ScrollbarGrabActive]    = color_interactive_clicked;
    colors[ImGuiCol_CheckMark]              = color_text;
    colors[ImGuiCol_SliderGrab]             = color_interactive;
    colors[ImGuiCol_SliderGrabActive]       = color_interactive_clicked;
    colors[ImGuiCol_Button]                 = color_interactive;
    colors[ImGuiCol_ButtonHovered]          = color_interactive_hovered;
    colors[ImGuiCol_ButtonActive]           = color_interactive_clicked;
    colors[ImGuiCol_Header]                 = color_interactive;            // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
    colors[ImGuiCol_HeaderHovered]          = color_interactive_hovered;
    colors[ImGuiCol_HeaderActive]           = color_interactive_clicked;
    colors[ImGuiCol_Separator]              = color_interactive;
    colors[ImGuiCol_SeparatorHovered]       = color_interactive_hovered;
    colors[ImGuiCol_SeparatorActive]        = color_interactive_clicked;
    colors[ImGuiCol_ResizeGrip]             = color_interactive;
    colors[ImGuiCol_ResizeGripHovered]      = color_interactive_hovered;
    colors[ImGuiCol_ResizeGripActive]       = color_interactive_clicked;
    colors[ImGuiCol_Tab]                    = color_interactive;
    colors[ImGuiCol_TabHovered]             = color_interactive_hovered;
    colors[ImGuiCol_TabActive]              = color_interactive_clicked;
    colors[ImGuiCol_TabUnfocused]           = color_interactive;
    colors[ImGuiCol_TabUnfocusedActive]     = color_interactive;            // Might be called active, but it's active only because it's it's the only tab available, the user didn't really activate it
    colors[ImGuiCol_DockingPreview]         = color_interactive_clicked;    // Preview overlay color when about to docking something
    colors[ImGuiCol_DockingEmptyBg]         = color_interactive;            // Background color for empty node (e.g. CentralNode with no window docked into it)
    colors[ImGuiCol_PlotLines]              = color_interactive;
    colors[ImGuiCol_PlotLinesHovered]       = color_interactive_hovered;
    colors[ImGuiCol_PlotHistogram]          = color_interactive;
    colors[ImGuiCol_PlotHistogramHovered]   = color_interactive_hovered;
    colors[ImGuiCol_TextSelectedBg]         = color_background;
    colors[ImGuiCol_DragDropTarget]         = color_interactive_hovered;    // Color when hovering over target
    colors[ImGuiCol_NavHighlight]           = color_background;             // Gamepad/keyboard: current highlighted item
    colors[ImGuiCol_NavWindowingHighlight]  = color_background;             // Highlight window when using CTRL+TAB
    colors[ImGuiCol_NavWindowingDimBg]      = color_background;             // Darken/colorize entire screen behind the CTRL+TAB window list, when active
    colors[ImGuiCol_ModalWindowDimBg]       = color_background;             // Darken/colorize entire screen behind a modal window, when one is active

    // Spatial settings
    const auto font_size    = 24.0f;
    const auto font_scale   = 0.7f;
    const auto roundness    = 2.0f;

    // Spatial
    ImGuiStyle& style               = ImGui::GetStyle();
    style.WindowBorderSize          = 1.0f;
    style.FrameBorderSize           = 0.0f;
    style.ScrollbarSize             = 20.0f;
    style.FramePadding              = ImVec2(5, 5);
    style.ItemSpacing               = ImVec2(6, 5);
    style.WindowMenuButtonPosition  = ImGuiDir_Right;
    style.WindowRounding            = roundness;
    style.FrameRounding             = roundness;
    style.PopupRounding             = roundness;
    style.GrabRounding              = roundness;
    style.ScrollbarRounding         = roundness;
    style.Alpha                     = 1.0f;
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
            ImGuiID dockUpID = ImGui::DockBuilderSplitNode(dockMainID, ImGuiDir_Up, 0.25f, nullptr, &dockMainID);

            //Docks widgets here
            ImGui::DockBuilderDockWindow("Assets", dockDownID);
            ImGui::DockBuilderDockWindow("Viewport", dockMainID);
            ImGui::DockBuilderDockWindow("Properties", dockRightID);
            ImGui::DockBuilderDockWindow("Hierarchy", dockRightID);
            ImGui::DockBuilderDockWindow("Hierarchy", dockUpID);

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