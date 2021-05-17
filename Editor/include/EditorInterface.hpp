#ifndef BWATENGINE_EDITORINTERFACE_HPP
#define BWATENGINE_EDITORINTERFACE_HPP

#include <vector>
#include <memory>

#include "ECS/ECS.hpp"
#include "Widget.hpp"
#include "Window.hpp"
#include "ImGuizmo.h"

namespace BwatEngine
{
    class Engine;
}

class WidgetProperties;

class  EditorInterface
{
public:
    EditorInterface(BwatEngine::Engine* _engine);
    ~EditorInterface() = default;

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


private:
    void ApplyStyle() const;
    void BeginWindow();

    BwatEngine::EntityID editedEntity = 0;
    std::vector<std::unique_ptr<Widget>> widgets;
    bool initialised = false;
    bool editorBegun = false;
    bool showFPS = false;
    const float toolBarSize = 45.f;
};




#endif //BWATENGINE_EDITORINTERFACE_HPP

