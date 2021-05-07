#ifndef BWATENGINE_WIDGETHIERARCHY_HPP
#define BWATENGINE_WIDGETHIERARCHY_HPP

#include "Widget.hpp"
#include "ECS/ECS.hpp"

class WidgetHierarchy : public Widget
{
public:
    WidgetHierarchy(EditorInterface* editor);
    void TickVisible() override;

private:
    void ShowEntity(BwatEngine::EntityID entity);
};
#endif //BWATENGINE_WIDGETHIERARCHY_HPP
