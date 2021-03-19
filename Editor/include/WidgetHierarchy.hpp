#ifndef BWATENGINE_WIDGETHIERARCHY_HPP
#define BWATENGINE_WIDGETHIERARCHY_HPP

#include "Widget.hpp"
#include <memory>
#include <ECS/Entity.hpp>

class WidgetHierarchy : public Widget
{
public:
    WidgetHierarchy(EditorInterface* editor);
    void TickVisible() override;
};
#endif //BWATENGINE_WIDGETHIERARCHY_HPP
