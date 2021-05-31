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
    va_list ap;
    va_copy(ap, ev->ap);

    size_t size = (size_t)vsnprintf(nullptr, 0, ev->fmt, ap);
    if (buffer.size() < size+1)
        buffer.resize(size+1);

    vsprintf(buffer.data(), ev->fmt, ev->ap);
    ss << buffer.data() << "\n";
}

void WidgetLog::TickVisible()
{
    ImGui::TextWrapped(ss.str().c_str());
    //printf("%s\n\n", ss.str().c_str());
}