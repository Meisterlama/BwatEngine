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



namespace BwatEngine
{
    class Engine;
}

class WidgetProperties;
class WidgetLoadSave;

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
    static ImGuizmo::MODE guizmoMode;
    static ImGuizmo::OPERATION guizmoOperation;
    Rendering::FrameBufferObject gameViewFramebuffer;
    Rendering::FrameBufferObject sceneViewFramebuffer;
    void ApplyStyle() const;

    fs::path currentScene;


    BwatEngine::CameraComponent camera;
    BwatEngine::TransformComponent cameraTransform;
    BwatEngine::Math::Vec3f rotation{};


    bool cursorLocked = false;
private:
    void BeginWindow();

    GLuint playImage = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/play.png",Rendering::Texture::Type::E_DIFFUSE)->id;
    BwatEngine::EntityID editedEntity = 0;
    std::vector<std::unique_ptr<Widget>> widgets;
    bool initialised = false;
    bool editorBegun = false;
    const float toolBarSize = 45.f;

    void HandleEditorShortcuts();
};




#endif //BWATENGINE_EDITORINTERFACE_HPP

