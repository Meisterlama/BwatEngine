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
    int size = vsnprintf(nullptr, 0, ev->fmt, ev->ap);
    if (buffer.size() < size)
        buffer.resize(size+1);

    vsnprintf(buffer.data(), buffer.size(), ev->fmt, ev->ap);
    ss << buffer.data() << "\n";
    std::string yolo = ss.str();
}

void WidgetLog::TickVisible()
{
    ImGui::TextWrapped(ss.str().c_str());
    //printf("%s\n\n", ss.str().c_str());
}