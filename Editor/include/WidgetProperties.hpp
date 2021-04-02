#ifndef BWATENGINE_WIDGETPROPERTIES_H
#define BWATENGINE_WIDGETPROPERTIES_H

#include "Widget.hpp"
#include <memory>
#include "Core.hpp"
#include <ECS/Components/TransformComponent.hpp>

class WidgetProperties : public Widget
{
public:
    WidgetProperties(EditorInterface* editor);

    void TickVisible() override;

    static void Inspect(BwatEngine::Entity& entity);

    static BwatEngine::Entity currentEntity;

private:
    template<typename T>
    void ShowComponent(T& component);

    template<typename T>
    bool AddComponentMenuItem(BwatEngine::Entity entity);

    template<typename T>
    bool ShowComponentMenuItem(BwatEngine::Entity entity);

};

#endif //BWATENGINE_WIDGETPROPERTIES_H
