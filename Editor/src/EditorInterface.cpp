
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "EditorInterface.hpp"
#include "WidgetMenuBar.hpp"
#include "WidgetHierarchy.hpp"
#include "WidgetAsset.hpp"
#include "WidgetShader.hpp"
#include "WidgetViewport.hpp"
#include "WidgetGameport.hpp"
#include "WidgetProperties.hpp"
#include "WidgetLog.hpp"
#include "WidgetPostProcess.hpp"
#include "WidgetSavePicker.hpp"
#include "WidgetLoadPicker.hpp"

#include "imgui_internal.h"
#include "Serialization/Serialization.hpp"
#include "Time.hpp"
#include "Engine.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/TransformComponent.hpp"

#include "Inputs/InputHandler.hpp"

ImGuizmo::MODE EditorInterface::guizmoMode = ImGuizmo::MODE::LOCAL;
ImGuizmo::OPERATION EditorInterface::guizmoOperation = ImGuizmo::OPERATION::TRANSLATE;

EditorInterface::EditorInterface(BwatEngine::Engine* _engine)
    : gameViewFramebuffer(_engine->GetWindow().GetWidth(), _engine->GetWindow().GetHeight())
    , sceneViewFramebuffer(_engine->GetWindow().GetWidth(), _engine->GetWindow().GetHeight())
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
    auto& coordinator = BwatEngine::Coordinator::GetInstance();

    auto renderSystem = coordinator.GetSystem<BwatEngine::RenderSystem>();

    // Render game in editor framebuffer
    GLint previousFramebuffer = gameViewFramebuffer.Bind();
    engine->Update();
    sceneViewFramebuffer.Bind();
    renderSystem->RenderWithCamera(camera, cameraTransform);
    glBindFramebuffer(GL_FRAMEBUFFER, previousFramebuffer);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (!engine->isPlaying && !cursorLocked)
    {
        HandleEditorShortcuts();
    }

    BeginWindow();
    ToolbarUI();

    for (std::unique_ptr<Widget>& widget : widgets)
    {
        widget->Tick();
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void EditorInterface::HandleEditorShortcuts()
{
    auto& coordinator = BwatEngine::Coordinator::GetInstance();
    if (BwatEngine::InputHandler::GetKeyboardDown(BwatEngine::KEY_W))
        guizmoOperation = ImGuizmo::TRANSLATE;
    if (BwatEngine::InputHandler::GetKeyboardDown(BwatEngine::KEY_E))
        guizmoOperation = ImGuizmo::ROTATE;
    if (BwatEngine::InputHandler::GetKeyboardDown(BwatEngine::KEY_R))
        guizmoOperation = ImGuizmo::SCALE;
    if (BwatEngine::InputHandler::GetKeyboardDown(BwatEngine::KEY_F))
    {
        if (editedEntity != 0 && coordinator.HaveComponent<BwatEngine::TransformComponent>(editedEntity))
        {
            auto entityPosition = coordinator.GetComponent<BwatEngine::TransformComponent>(editedEntity).position;
            auto offset = entityPosition - cameraTransform.position;
            cameraTransform.rotation = BwatEngine::Math::Quatf::LookAt(entityPosition, cameraTransform.position, BwatEngine::Math::Vec3f{0, 1, 0});
            rotation = cameraTransform.rotation.GetEulerAngles();
            if (offset.Z > 0)
            {
                rotation.Y = BwatEngine::Math::PI - rotation.Y;
            }
            rotation.X = BwatEngine::Math::Loop(rotation.X, -BwatEngine::Math::PI / 2, BwatEngine::Math::PI / 2);
            rotation.Y = BwatEngine::Math::Loop(rotation.Y, 0, BwatEngine::Math::PI * 2);
            rotation.Z = 0;
        }
    }
    if (BwatEngine::InputHandler::GetKeyboardDown(BwatEngine::KEY_ESCAPE))
    {
        SetEditedEntity(0);
    }
}

void EditorInterface::Initialise()
{
    ApplyStyle();

    //Push widget here
    widgets.emplace_back(std::make_unique<WidgetMenuBar>(this)); // 0 = MenuBar
    widgets.emplace_back(std::make_unique<WidgetHierarchy>(this)); // 1 = Hierarchy
    widgets.emplace_back(std::make_unique<WidgetAsset>(this)); // 2 = Asset
    widgets.emplace_back(std::make_unique<WidgetViewport>(this)); // 3 = Viewport
    widgets.emplace_back(std::make_unique<WidgetGameport>(this)); // 4 = Gameport
    widgets.emplace_back(std::make_unique<WidgetLog>(this)); // 4 = Log
    widgets.emplace_back(std::make_unique<WidgetShader>(this)); // 5 = Shader
    widgets.emplace_back(std::make_unique<WidgetPostProcess>(this)); // 6 = PostProcess
    widgets.emplace_back(std::make_unique<WidgetSavePicker>(this)); // 7 = Save
    widgets.emplace_back(std::make_unique<WidgetLoadPicker>(this)); // 8 = Load

    {
        widgets.emplace_back(std::make_unique<WidgetProperties>(this)); // Properties always last
        widgetProperties = static_cast<WidgetProperties*>(widgets.back().get());
    }
}

void EditorInterface::ApplyStyle() const
{
    // Color settings
    const auto color_text                   = ImVec4(1.f, 1.f, 1.f, 1.f);
    const auto color_text_disabled          = ImVec4(color_text.x, color_text.y, color_text.z, 0.5f);
    const auto color_interactive            = ImVec4(176.f  / 255.f, 46.f  / 255.f, 12.f  / 255.f, 1.f);
    const auto color_interactive_hovered    = ImVec4(235.f / 255.f, 69.f / 255.f, 17.f / 255.f, 1.f);
    const auto color_background             = ImVec4(60.f  / 255.f, 60.f  / 255.f, 60.f  / 255.f, 1.f);
    const auto color_background_content     = ImVec4(201.f  / 255.f, 70.f  / 255.f, 40.f  / 255.f, 1.f);
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
    colors[ImGuiCol_FrameBgActive]          = color_interactive_hovered;
    colors[ImGuiCol_TitleBg]                = color_background_content;
    colors[ImGuiCol_TitleBgActive]          = color_interactive;
    colors[ImGuiCol_TitleBgCollapsed]       = color_background;
    colors[ImGuiCol_MenuBarBg]              = color_background_content;
    colors[ImGuiCol_ScrollbarBg]            = color_background_content;
    colors[ImGuiCol_ScrollbarGrab]          = color_interactive;
    colors[ImGuiCol_ScrollbarGrabHovered]   = color_interactive_hovered;
    colors[ImGuiCol_ScrollbarGrabActive]    = color_interactive_hovered;
    colors[ImGuiCol_CheckMark]              = color_text;
    colors[ImGuiCol_SliderGrab]             = color_interactive;
    colors[ImGuiCol_SliderGrabActive]       = color_interactive_hovered;
    colors[ImGuiCol_Button]                 = color_interactive;
    colors[ImGuiCol_ButtonHovered]          = color_interactive_hovered;
    colors[ImGuiCol_ButtonActive]           = color_interactive_hovered;
    colors[ImGuiCol_Header]                 = color_interactive;            // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
    colors[ImGuiCol_HeaderHovered]          = color_interactive_hovered;
    colors[ImGuiCol_HeaderActive]           = color_interactive_hovered;
    colors[ImGuiCol_Separator]              = color_interactive;
    colors[ImGuiCol_SeparatorHovered]       = color_interactive_hovered;
    colors[ImGuiCol_SeparatorActive]        = color_interactive_hovered;
    colors[ImGuiCol_ResizeGrip]             = color_interactive;
    colors[ImGuiCol_ResizeGripHovered]      = color_interactive_hovered;
    colors[ImGuiCol_ResizeGripActive]       = color_interactive_hovered;
    colors[ImGuiCol_Tab]                    = color_interactive;
    colors[ImGuiCol_TabHovered]             = color_interactive_hovered;
    colors[ImGuiCol_TabActive]              = color_interactive_hovered;
    colors[ImGuiCol_TabUnfocused]           = color_interactive;
    colors[ImGuiCol_TabUnfocusedActive]     = color_interactive;            // Might be called active, but it's active only because it's it's the only tab available, the user didn't really activate it
    colors[ImGuiCol_DockingPreview]         = color_interactive_hovered;    // Preview overlay color when about to docking something
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
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + toolBarSize));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y - toolBarSize));
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
void EditorInterface::ToolbarUI()
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + ImGui::GetCurrentWindow()->MenuBarHeight()));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, toolBarSize));
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags window_flags = 0
                                    | ImGuiWindowFlags_NoDocking
                                    | ImGuiWindowFlags_NoTitleBar
                                    | ImGuiWindowFlags_NoResize
                                    | ImGuiWindowFlags_NoMove
                                    | ImGuiWindowFlags_NoScrollbar
                                    | ImGuiWindowFlags_NoSavedSettings
    ;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::Begin("TOOLBAR", NULL, window_flags);
    ImGui::PopStyleVar();

    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/trans.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(25.f, 25.f)))
    {
        guizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/rotate.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(25.f, 25.f)))
    {
        guizmoOperation = ImGuizmo::OPERATION::ROTATE;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/scale.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(25.f, 25.f)))
    {
        guizmoOperation = ImGuizmo::OPERATION::SCALE;
    }
    ImGui::SameLine();
    ImGui::Text("Pos X:%.3f Y:%.3f Z:%.3f\nRot X:%.3f Y:%.3f Z:%.3f",
                cameraTransform.position.X, cameraTransform.position.Y, cameraTransform.position.Z,
                BwatEngine::Math::ToDegs(rotation.X), BwatEngine::Math::ToDegs(rotation.Y), BwatEngine::Math::ToDegs(rotation.Z));

    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 125);
    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/world.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(25.f, 25.f)))
    {
        guizmoMode = ImGuizmo::MODE::WORLD;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/local.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(25.f, 25.f)))
    {
        guizmoMode = ImGuizmo::MODE::LOCAL;
    }

    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetWindowWidth()/2 - 25/2);
    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(playImage), ImVec2(25.f, 25.f)))
    {
        if (!engine->isPlaying)
        {
            BwatEngine::Serializer::SaveScene("temp.txt");
            engine->isPlaying = true;
            playImage = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/pause.png",Rendering::Texture::Type::E_DIFFUSE)->id;
            ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(235.f / 255.f, 69.f / 255.f, 17.f / 255.f, 1.f);

            SetEditedEntity(0);
        }
        else
        {
            engine->isPlaying = false;
            BwatEngine::Serializer::LoadScene("temp.txt");
            playImage = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/play.png",Rendering::Texture::Type::E_DIFFUSE)->id;
            ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(60.f  / 255.f, 60.f  / 255.f, 60.f  / 255.f, 1.f);
        }
    }

    ImGui::End();
}