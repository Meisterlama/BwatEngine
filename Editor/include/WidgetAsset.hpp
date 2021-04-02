#ifndef BWATENGINE_WIDGETASSET_H
#define BWATENGINE_WIDGETASSET_H

#include "Widget.hpp"

class WidgetAsset : public Widget
{
public:
    WidgetAsset(EditorInterface* editor);

    void TickVisible() override;
};

#endif //BWATENGINE_WIDGETASSET_H
