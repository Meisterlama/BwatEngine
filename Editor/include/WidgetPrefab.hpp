#ifndef BWATENGINE_WIDGETPREFAB_HPP
#define BWATENGINE_WIDGETPREFAB_HPP

#include "Widget.hpp"
#include "FileDialog.hpp"
#include "ECS/Coordinator.hpp"

class WidgetPrefab : public Widget
{
public:
    WidgetPrefab(EditorInterface* editor);


    void TickVisible() override;

    void Open(bool saving, BwatEngine::EntityID entityId = 0);

private:
    bool saving = false;
    FileDialog fileDialog;
    std::string fileName;

    std::string buttonText;
    bool textReadOnly;

    BwatEngine::EntityID selectedEntity = 0;
};

#endif //BWATENGINE_WIDGETPREFAB_HPP
