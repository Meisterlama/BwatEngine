#ifndef BWATENGINE_WIDGETPROPERTIES_H
#define BWATENGINE_WIDGETPROPERTIES_H

#include "Widget.hpp"
#include "Math/Vector/Vector3.hpp"
#include "ECS/ECS.hpp"

class WidgetProperties : public Widget
{
public:
    WidgetProperties(EditorInterface* editor);

    void TickVisible() override;

    void Inspect(BwatEngine::EntityID entity);

    BwatEngine::Math::Vec3f eulersInDegrees; // Value to edit before converted to quaternion

private:
    template<typename T>
    void ShowComponent(T& component);

    template<typename T>
    bool AddComponentMenuItem(BwatEngine::EntityID entity);

    template<typename T>
    bool ShowComponentMenuItem(BwatEngine::EntityID entity);

    BwatEngine::EntityID currentEntity = 0;
};

#endif //BWATENGINE_WIDGETPROPERTIES_H
