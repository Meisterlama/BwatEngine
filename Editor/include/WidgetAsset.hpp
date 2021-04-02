#ifndef BWATENGINE_WIDGETASSET_H
#define BWATENGINE_WIDGETASSET_H

#include "Widget.hpp"
#include "FileDialog.hpp"

class WidgetAsset : public Widget
{
public:
    WidgetAsset(EditorInterface* editor);

    FileDialog assetDirectory;

    void TickVisible() override;
};

#endif //BWATENGINE_WIDGETASSET_H
