#ifndef BWATENGINE_WIDGETPROPERTIES_H
#define BWATENGINE_WIDGETPROPERTIES_H

#include "Widget.hpp"
#include "ECS/ECS.hpp"

class WidgetProperties : public Widget
{
public:
    WidgetProperties(EditorInterface* editor);

    void TickVisible() override;

    static void Inspect(BwatEngine::EntityID entity);

    static BwatEngine::EntityID currentEntity;

private:
    template<typename T>
    void ShowComponent(T& component);

    template<typename T>
    bool AddComponentMenuItem(BwatEngine::EntityID entity);

    template<typename T>
    bool ShowComponentMenuItem(BwatEngine::EntityID entity);

};

#endif //BWATENGINE_WIDGETPROPERTIES_H
