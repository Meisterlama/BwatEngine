
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
#include "WidgetOption.hpp"
#include "WidgetLoadSave.hpp"
#include "WidgetPrefab.hpp"

#include "imgui_internal.h"
#define SERIALIZATION_IMPLEMENTATION
#include "Serialization/Serialization.hpp"
#include "Time.hpp"
#include "Engine.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Systems/ColliderDrawSystem.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/ColliderComponent.hpp"

#include "Inputs/InputHandler.hpp"
#include "json.hpp"

using json = nlohmann::json;

ImGuizmo::MODE EditorInterface::guizmoMode = ImGuizmo::MODE::LOCAL;
ImGuizmo::OPERATION EditorInterface::guizmoOperation = ImGuizmo::OPERATION::TRANSLATE;

EditorInterface::EditorInterface(BwatEngine::Engine* _engine)
    : gameViewFramebuffer(_engine->GetWindow().GetWidth(), _engine->GetWindow().GetHeight())
    , sceneViewFramebuffer(_engine->GetWindow().GetWidth(), _engine->GetWindow().GetHeight())
{
    using namespace BwatEngine;
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

    LoadData("editor.conf");

    auto& coordinator = Coordinator::GetInstance();

    coordinator.RegisterSystem<ColliderDrawSystem>();
    coordinator.SetSystemSignature<ColliderDrawSystem, TransformComponent, ColliderComponent>();
    coordinator.SetSystemConfig<ColliderDrawSystem>(SystemConfig{SystemConfig::ManualUpdate});

    if (!currentScene.empty())
    {
        BwatEngine::Serialization::LoadScene(currentScene.string().c_str());
    }

    camera.near = 0.01f;
}

void EditorInterface::Close()
{
    std::remove("EngineAssets/temp.bwat");
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void EditorInterface::OnTick()
{
    auto& coordinator = BwatEngine::Coordinator::GetInstance();

    auto renderSystem = coordinator.GetSystem<BwatEngine::RenderSystem>();
    auto colliderDrawSystem = coordinator.GetSystem<BwatEngine::ColliderDrawSystem>();

    // Render game in editor framebuffer
    GLint previousFramebuffer = gameViewFramebuffer.Bind();
    engine->Update();
    sceneViewFramebuffer.Bind();
    renderSystem->RenderWithCamera(camera, cameraTransform);
    colliderDrawSystem->DrawWithCamera(camera, cameraTransform);
    glBindFramebuffer(GL_FRAMEBUFFER, previousFramebuffer);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // pushfont to font 

    ImGui::PushFont(font);

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

    ImGui::PopFont();

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void EditorInterface::HandleEditorShortcuts()
{
    using namespace BwatEngine;
    auto& coordinator = Coordinator::GetInstance();
    if (InputHandler::GetKeyboard(KEY_LEFT_CONTROL))
    {
        if (InputHandler::GetKeyboardDown(KEY_D))
        {
            using namespace BwatEngine;
            EntityID duplicatedEntity = Serialization::LoadEntity(Serialization::SaveEntity(GetEditedEntity()));
            SetEditedEntity(duplicatedEntity);
        }
    }
    else
    {
        if (InputHandler::GetKeyboardDown(KEY_W))
            guizmoOperation = ImGuizmo::TRANSLATE;
        if (InputHandler::GetKeyboardDown(KEY_E))
            guizmoOperation = ImGuizmo::ROTATE;
        if (InputHandler::GetKeyboardDown(KEY_R))
            guizmoOperation = ImGuizmo::SCALE;
        if (InputHandler::GetKeyboardDown(KEY_F))
        {
            if (editedEntity != 0 && coordinator.HaveComponent<TransformComponent>(editedEntity))
            {
                auto entityPosition = coordinator.GetComponent<TransformComponent>(editedEntity).position;
                auto offset = entityPosition - cameraTransform.position;
                cameraTransform.rotation = Math::Quatf::LookAt(entityPosition, cameraTransform.position,
                                                               Math::Vec3f{0, 1, 0});
                rotation = cameraTransform.rotation.GetEulerAngles();
                if (offset.Z > 0)
                {
                    rotation.Y = Math::PI - rotation.Y;
                }
                rotation.X = Math::Loop(rotation.X, -Math::PI / 2, Math::PI / 2);
                rotation.Y = Math::Loop(rotation.Y, 0, Math::PI * 2);
                rotation.Z = 0;
            }
        }
        if (InputHandler::GetKeyboardDown(KEY_ESCAPE))
        {
            SetEditedEntity(0);
        }
        if (InputHandler::GetKeyboardDown(KEY_DELETE))
        {
            coordinator.DestroyEntity(editedEntity);
        }
    }
}

void EditorInterface::Initialise()
{
    ImGuiIO& io = ImGui::GetIO();
    font = io.Fonts->AddFontFromFileTTF("EngineAssets/Oxanium-Regular.ttf", 16.f);
    io.Fonts->Build();

    ApplyStyle();

    //Push widget here
    widgets.emplace_back(std::make_unique<WidgetMenuBar>(this)); // 0 = MenuBar
    widgets.emplace_back(std::make_unique<WidgetHierarchy>(this)); // 1 = Hierarchy
    widgets.emplace_back(std::make_unique<WidgetAsset>(this)); // 2 = Asset
    widgets.emplace_back(std::make_unique<WidgetViewport>(this)); // 3 = Viewport
    widgets.emplace_back(std::make_unique<WidgetGameport>(this)); // 4 = Gameport
    widgets.emplace_back(std::make_unique<WidgetLog>(this)); // 5 = Log
    widgets.emplace_back(std::make_unique<WidgetShader>(this)); // 6 = Shader
    widgets.emplace_back(std::make_unique<WidgetPostProcess>(this)); // 7 = PostProcess
    widgets.emplace_back(std::make_unique<WidgetOption>(this)); // 8 = Options


    {
        widgets.emplace_back(std::make_unique<WidgetLoadSave>(this)); // 9 = Load
        widgetLoadSave = static_cast<WidgetLoadSave*>(widgets.back().get());
    }
    {
        widgets.emplace_back(std::make_unique<WidgetPrefab>(this)); // 9 = Load
        widgetPrefab = static_cast<WidgetPrefab*>(widgets.back().get());
    }
    {
        widgets.emplace_back(std::make_unique<WidgetProperties>(this)); // Properties always last
        widgetProperties = static_cast<WidgetProperties*>(widgets.back().get());
    }
}

ImVec4 BwatVec4toImVec4(BwatEngine::Math::Vec4f vec)
{
    ImVec4 vecteur = ImVec4(vec.X, vec.Y, vec.Z, vec.W);
    return vecteur;
}

void EditorInterface::ApplyStyle(bool isBasic) const
{
    // Color settings
    ImVec4 color_text                   = BwatVec4toImVec4(style.colorText);
    ImVec4 color_text_disabled          = BwatVec4toImVec4(style.colorText);
    ImVec4 color_interactive_hovered    = BwatVec4toImVec4(style.colorInteractiveHovered);
    ImVec4 color_background             = BwatVec4toImVec4(style.colorBackground);
    ImVec4 color_background_content     = BwatVec4toImVec4(style.colorBackgroundContent);
    ImVec4 colorBarActive               = BwatVec4toImVec4(style.colorTabActive);
    ImVec4 color_interactive            = BwatVec4toImVec4(style.colorInteractive);
    ImVec4 gold                         = BwatVec4toImVec4(style.colorGoldInteractive);
    ImVec4 goldActive                   = BwatVec4toImVec4(style.colorGoldActive);
    ImVec4 titlebg                      = BwatVec4toImVec4(style.colortitlebg);

    if (!isBasic)
    {
        gold = color_interactive;
        color_interactive = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    }



    // Colors
    ImVec4* colors                          = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = color_text;
    colors[ImGuiCol_TextDisabled]           = color_text_disabled;
    colors[ImGuiCol_WindowBg]               = color_background;             // Background of normal windows
    colors[ImGuiCol_ChildBg]                = color_background;             // Background of child windows
    colors[ImGuiCol_PopupBg]                = color_background_content;             // Background of popups, menus, tooltips windows
    colors[ImGuiCol_Border]                 = color_interactive;
    colors[ImGuiCol_BorderShadow]           = color_text;
    colors[ImGuiCol_FrameBg]                = color_background_content;     // Background of checkbox, radio button, plot, slider, text input
    colors[ImGuiCol_FrameBgHovered]         = color_interactive;
    colors[ImGuiCol_FrameBgActive]          = color_interactive_hovered;
    colors[ImGuiCol_TitleBg]                = titlebg;
    colors[ImGuiCol_TitleBgActive]          = colorBarActive;
    colors[ImGuiCol_TitleBgCollapsed]       = color_text;
    colors[ImGuiCol_MenuBarBg]              = color_background_content;
    colors[ImGuiCol_ScrollbarBg]            = color_background_content;
    colors[ImGuiCol_ScrollbarGrab]          = color_interactive;
    colors[ImGuiCol_ScrollbarGrabHovered]   = color_interactive_hovered;
    colors[ImGuiCol_ScrollbarGrabActive]    = color_interactive_hovered;
    colors[ImGuiCol_CheckMark]              = color_text;
    colors[ImGuiCol_SliderGrab]             = colorBarActive;
    colors[ImGuiCol_SliderGrabActive]       = colorBarActive;
    colors[ImGuiCol_Button]                 = color_interactive;
    colors[ImGuiCol_ButtonHovered]          = gold;
    colors[ImGuiCol_ButtonActive]           = color_interactive_hovered;
    colors[ImGuiCol_Header]                 = color_interactive;            // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
    colors[ImGuiCol_HeaderHovered]          = gold;
    colors[ImGuiCol_HeaderActive]           = color_interactive_hovered;
    colors[ImGuiCol_Separator]              = color_interactive;
    colors[ImGuiCol_SeparatorHovered]       = color_interactive_hovered;
    colors[ImGuiCol_SeparatorActive]        = color_interactive_hovered;
    colors[ImGuiCol_ResizeGrip]             = color_interactive;
    colors[ImGuiCol_ResizeGripHovered]      = color_interactive_hovered;
    colors[ImGuiCol_ResizeGripActive]       = color_interactive_hovered;
    colors[ImGuiCol_Tab]                    = color_interactive;
    colors[ImGuiCol_TabHovered]             = gold;
    colors[ImGuiCol_TabActive]              = goldActive;
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
    const auto roundness    = style.roundness;

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
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1);
    ImGui::Begin("TOOLBAR", NULL, window_flags);
    ImGui::PopStyleVar();

    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("EngineAssets/Images/trans.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(25.f, 25.f)))
    {
        guizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("EngineAssets/Images/rotate.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(25.f, 25.f)))
    {
        guizmoOperation = ImGuizmo::OPERATION::ROTATE;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("EngineAssets/Images/scale.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(25.f, 25.f)))
    {
        guizmoOperation = ImGuizmo::OPERATION::SCALE;
    }

    ImGui::SameLine();
    ImGui::Text("Pos X:%.3f Y:%.3f Z:%.3f\nRot X:%.3f Y:%.3f Z:%.3f",
                cameraTransform.position.X, cameraTransform.position.Y, cameraTransform.position.Z,
                BwatEngine::Math::ToDegs(rotation.X), BwatEngine::Math::ToDegs(rotation.Y), BwatEngine::Math::ToDegs(rotation.Z));

    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 125);

    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("EngineAssets/Images/world.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(25.f, 25.f)))
    {
        guizmoMode = ImGuizmo::MODE::WORLD;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("EngineAssets/Images/local.png",Rendering::Texture::Type::E_DIFFUSE)->id), ImVec2(25.f, 25.f)))
    {
        guizmoMode = ImGuizmo::MODE::LOCAL;
    }

    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetWindowWidth()/2 - 25/2);
    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(playImage), ImVec2(25.f, 25.f)))
    {
        if (!engine->isPlaying)
        {
            tempSave = Serialization::SerializeScene();
            engine->isPlaying = true;
            playImage = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("EngineAssets/Images/pause.png",Rendering::Texture::Type::E_DIFFUSE)->id;
            ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = BwatVec4toImVec4(style.colorGoldActive);

            SetEditedEntity(0);
        }
        else
        {
            engine->isPlaying = false;
            Serialization::DeserializeScene(tempSave);
            tempSave.clear();
            playImage = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("EngineAssets/Images/play.png",Rendering::Texture::Type::E_DIFFUSE)->id;
            ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = BwatVec4toImVec4(style.colorBackground);
        }
    }

    ImGui::End();
}

void EditorInterface::SaveData(const char* path)
{
    std::ofstream file(path);

    json js;
    std::string lastScenePath = fs::relative(currentScene, fs::current_path()).string();

    js["LastScene"] = lastScenePath;
    file << js << std::endl;
}

void EditorInterface::LoadData(const char* path)
{
    std::ifstream file(path);

    if (!file)
    {
        LogError("No File at path :%s", path);
        return;
    }

    json js;
    file >> js;


    if (js.contains("LastScene"))
        currentScene = js.at("LastScene").get<std::string>();
}