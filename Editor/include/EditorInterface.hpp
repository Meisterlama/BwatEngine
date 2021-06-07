#ifndef BWATENGINE_EDITORINTERFACE_HPP
#define BWATENGINE_EDITORINTERFACE_HPP

#include <vector>
#include <memory>
#include <ECS/Coordinator.hpp>

#include "ECS/ECS.hpp"
#include "Widget.hpp"
#include "Window.hpp"
#include "ImGuizmo.h"
#include "Rendering/FrameBuffer.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"

#include "Serialization/Serialization.hpp"



namespace BwatEngine
{
    class Engine;
}

class WidgetProperties;
class WidgetLoadSave;
class WidgetPrefab;

struct StyleUI
{
    BwatEngine::Math::Vec4f colorText = {1};
    BwatEngine::Math::Vec4f colorBackground = { 0.235f, 0.235f, 0.235f, 1.f };
    BwatEngine::Math::Vec4f colorBackgroundContent = { 0.441f, 0.441f, 0.441f, 1.f };
    BwatEngine::Math::Vec4f colorInteractiveHovered = { 0.714f , 0.714f, 0.714f, 1.f };
    BwatEngine::Math::Vec4f colorTabActive = { 160 / 255.f, 160 / 255.f, 160 / 255.f, 1.f };
    BwatEngine::Math::Vec4f colorInteractive = { 0.63f, 0.545f, 0.074f, 1 };
    BwatEngine::Math::Vec4f colorGoldInteractive = { 92 / 255.f, 91 / 255.f, 18 / 255.f, 1.f };
    BwatEngine::Math::Vec4f colorGoldActive = { 62 / 255.f, 61 / 255.f, 12 / 255.f, 1.f };
    BwatEngine::Math::Vec4f colortitlebg = { 110 / 255.f, 110 / 255.f, 110 / 255.f, 1.f };

    float roundness = 4.f;

};

class  EditorInterface
{
public:
    EditorInterface(BwatEngine::Engine* _engine);
    ~EditorInterface()
    {
        SaveData("editor.conf");
        Close();
    };

    void OnTick();
    void Initialise();
    void Close();
    void ToolbarUI();
    void SaveData(const char* path);
    void LoadData(const char* path);

    void SetEditedEntity(BwatEngine::EntityID entity);
    std::vector<std::unique_ptr<Widget>>&  GetWidgetList() { return widgets; };
    BwatEngine::EntityID GetEditedEntity() { return editedEntity; }

    BwatEngine::Engine* engine = nullptr;
    WidgetProperties* widgetProperties = nullptr;
    WidgetLoadSave* widgetLoadSave = nullptr;
    WidgetPrefab* widgetPrefab = nullptr;
    static ImGuizmo::MODE guizmoMode;
    static ImGuizmo::OPERATION guizmoOperation;
    Rendering::FrameBufferObject gameViewFramebuffer;
    Rendering::FrameBufferObject sceneViewFramebuffer;
    void ApplyStyle(bool isBasic = true) const;

    fs::path currentScene;
    json tempSave;

    BwatEngine::CameraComponent camera;
    BwatEngine::TransformComponent cameraTransform;
    BwatEngine::Math::Vec3f rotation{};

    bool cursorLocked = false;

    StyleUI style;

private:
    void BeginWindow();

    GLuint playImage = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("EngineAssets/Images/play.png",Rendering::Texture::Type::E_DIFFUSE)->id;
    BwatEngine::EntityID editedEntity = 0;
    std::vector<std::unique_ptr<Widget>> widgets;
    bool initialised = false;
    bool editorBegun = false;
    const float toolBarSize = 50.f;
    ImFont* font = nullptr;

    void HandleEditorShortcuts();
};




#endif //BWATENGINE_EDITORINTERFACE_HPP

