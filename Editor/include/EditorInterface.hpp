#ifndef BWATENGINE_EDITORINTERFACE_HPP
#define BWATENGINE_EDITORINTERFACE_HPP

#include <vector>
#include <memory>

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

class  EditorInterface
{
public:
    EditorInterface(BwatEngine::Engine* _engine);
    ~EditorInterface()
    {
        Close();
    };

    void OnTick();
    void Initialise();
    void Close();
    void ToolbarUI();

    void SetEditedEntity(BwatEngine::EntityID entity);
    std::vector<std::unique_ptr<Widget>>&  GetWidgetList() { return widgets; };
    BwatEngine::EntityID GetEditedEntity() { return editedEntity; }

    BwatEngine::Engine* engine = nullptr;
    WidgetProperties* widgetProperties = nullptr;
    static ImGuizmo::MODE guizmoMode;
    static ImGuizmo::OPERATION guizmoOperation;
    Rendering::FrameBufferObject gameViewFramebuffer;
    void ApplyStyle() const;

    BwatEngine::CameraComponent camera;
    BwatEngine::TransformComponent cameraTransform;
    BwatEngine::Math::Vec3f rotation{};

private:
    void BeginWindow();
    GLuint playImage = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/play.png",Rendering::Texture::Type::E_DIFFUSE)->id;

    BwatEngine::EntityID editedEntity = 0;
    std::vector<std::unique_ptr<Widget>> widgets;
    bool initialised = false;
    bool editorBegun = false;
    bool showFPS = false;
    const float toolBarSize = 45.f;
};




#endif //BWATENGINE_EDITORINTERFACE_HPP

