#ifndef DEBUG_LOGGER_HPP
#define DEBUG_LOGGER_HPP

#include <cstdio>
#include <cstdarg>
#include <ctime>

namespace BLogger
{
    typedef struct LogEvent {
        va_list ap;
        const char *fmt;
        const char *file;
        struct tm *time;
        void *uData;
        int line;
        int level;
        }LogEvent;

    typedef void (*LogFn)(LogEvent *ev);
    typedef void (*LockFn)(bool lock, void *uData);

    enum { E_LOG_TRACE, E_LOG_DEBUG, E_LOG_INFO, E_LOG_WARN, E_LOG_ERROR, E_LOG_FATAL };

#if !defined(NDEBUG) || defined(BWATEDITOR)

#define LogTrace(...) LogLog(BLogger::E_LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__ )
#define LogDebug(...) LogLog(BLogger::E_LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__ )
#define LogInfo(...) LogLog(BLogger::E_LOG_INFO, __FILE__, __LINE__, __VA_ARGS__ )
#define LogWarn(...) LogLog(BLogger::E_LOG_WARN, __FILE__, __LINE__, __VA_ARGS__ )
#define LogError(...) LogLog(BLogger::E_LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__ )
#define LogFatal(...) LogLog(BLogger::E_LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__ )

#else

#define LogTrace(...)
#define LogDebug(...)
#define LogInfo(...)
#define LogWarn(...)
#define LogError(...)
#define LogFatal(...)

#endif

    const char* LogLevelString(int level);
    void LogSetLock(LockFn fn, void *uData);
    void LogSetLevel(int level);
    void LogSetQuiet(bool enable);
    int LogAddCallback(LogFn callback, void* uData, int level);
    void LogRemoveCallback(int index);
    int LogAddFp(FILE *fp, int level);

    void LogLog(int level, const char*file, int line, const char *fmt, ...);

    void LogNull();


    static bool isDirty = false;
}


#endif