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

#include <vector>
void WidgetLog::OnLogCallback(BLogger::LogEvent* ev)
{
    static std::vector<char> buffer; // Avoid allocation for each call
    va_list ap;
    va_copy(ap, ev->ap);

    int size = vsnprintf(nullptr, 0, ev->fmt, ap);
    if (buffer.size() < size)
        buffer.resize(size+1);

    vsprintf(buffer.data(), ev->fmt, ev->ap);
    ss << buffer.data() << "\n";
}

void WidgetLog::TickVisible()
{
    ImGui::TextWrapped(ss.str().c_str());
    //printf("%s\n\n", ss.str().c_str());
}