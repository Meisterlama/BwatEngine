#ifndef BWATENGINE_WIDGETPROPERTIES_H
#define BWATENGINE_WIDGETPROPERTIES_H

#include "Widget.hpp"
#include <memory>
#include <ECS/Entity.hpp>
#include <ECS/Components/TransformComponent.hpp>

class WidgetProperties : public Widget
{
public:
    WidgetProperties(EditorInterface* editor);

    void TickVisible() override;

    static void Inspect(BwatEngine::Entity& entity);

    static BwatEngine::Entity* currentEntity;

private:
    template<typename T>
    void ShowComponent(T& component);

};

#endif //BWATENGINE_WIDGETPROPERTIES_H