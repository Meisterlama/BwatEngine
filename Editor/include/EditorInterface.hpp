#ifndef BWATENGINE_EDITORINTERFACE_HPP
#define BWATENGINE_EDITORINTERFACE_HPP

#include <vector>
#include <memory>

#include "ECS/ECS.hpp"
#include "Widget.hpp"
#include "Window.hpp"

namespace BwatEngine
{
    class Engine;
}

class WidgetProperties;

class  EditorInterface
{
public:
    EditorInterface(BwatEngine::Engine* _engine);
    ~EditorInterface(){};

    void OnTick();
    void Initialise();

    void SetEditedEntity(BwatEngine::EntityID entity);
    BwatEngine::EntityID GetEditedEntity() { return editedEntity; }

    BwatEngine::Engine* engine = nullptr;
    WidgetProperties* widgetProperties = nullptr;

private:
    void ApplyStyle() const;
    void BeginWindow();

    BwatEngine::EntityID editedEntity = 0;
    std::vector<std::unique_ptr<Widget>> widgets;
    bool initialised = false;
    bool editorBegun = false;
};




#endif //BWATENGINE_EDITORINTERFACE_HPP

