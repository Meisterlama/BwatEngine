#ifndef BWATENGINE_WIDGETLOG_HPP
#define BWATENGINE_WIDGETLOG_HPP

#include "Widget.hpp"
#include <sstream>

namespace BLogger
{
    struct LogEvent;
}

// only log after the widget initialized
class WidgetLog : public Widget
{
public :
    WidgetLog(EditorInterface* editor);
    virtual ~WidgetLog();


    void TickVisible() override;
    void PrintDebug();

    void OnLogCallback(BLogger::LogEvent* ev);

private:
    std::stringstream ss {};
    int callbackIndex;

};



#endif