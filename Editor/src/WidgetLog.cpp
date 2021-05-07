#include "WidgetLog.hpp"
#include "Debug/Logger.hpp"

static void logCallback(BLogger::LogEvent *ev)
{
    WidgetLog* self = static_cast<WidgetLog*>(ev->uData);
    self->OnLogCallback(ev);
}

WidgetLog::WidgetLog(EditorInterface *editor): Widget(editor)
{
    title = "Logs";
    callbackIndex = BLogger::LogAddCallback(logCallback, this, 0);
}

WidgetLog::~WidgetLog()
{
    BLogger::LogRemoveCallback(callbackIndex);
}

void WidgetLog::OnLogCallback(BLogger::LogEvent* ev)
{
    char buffer[1024];
    vsprintf(buffer, ev->fmt, ev->ap);
    ss << buffer << "\n";
}

void WidgetLog::TickVisible()
{
    ImGui::Text(ss.str().c_str());
}