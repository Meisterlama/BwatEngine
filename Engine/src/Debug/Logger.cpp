#include "Debug/Logger.hpp"

#include <cstdio>

namespace BLogger
{
    #define MAX_CALLBACKS 32

typedef struct {
        LogFn fn;
        void *uData;
        int level;
}Callback;

static struct {
        void *uData;
        LockFn lock;
        int level;
        bool quiet;
        Callback callbacks[MAX_CALLBACKS];
}L;

static const char *LevelStrings[] = {
        "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

#ifdef LOG_USE_COLOR
static const char *LevelColors[] = {
        "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};
#endif

    static void stdoutCallback(LogEvent *ev) {
        char buf[16];
        buf[strftime(buf, sizeof(buf), "%H:%M:%S", ev->time)] = '\0';

        #ifdef LOG_USE_COLOR
        std::fprintf(
            (FILE*)ev->uData, "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ",
            buf, LevelColors[ev->level], LevelStrings[ev->level],
            ev->file, ev->line);
#else
        std::fprintf(
                (FILE*)ev->uData, "%s %-5s %s:%d: ",
            buf, LevelStrings[ev->level], ev->file, ev->line);
#endif
        std::vfprintf((FILE*) ev->uData, ev->fmt, ev->ap);
        std::fprintf((FILE*)ev->uData, "\n");
        std::fflush((FILE*)ev->uData);
    }

    static void FileCallback(LogEvent *ev) {
        char buf[64];
        buf[strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ev->time)] = '\0';
        std::fprintf(
                (FILE*)ev->uData, "%s %-5s %s:%d: ",
            buf, LevelStrings[ev->level], ev->file, ev->line);
        std::vfprintf((FILE*)ev->uData, ev->fmt, ev->ap);
        std::fprintf((FILE*)ev->uData, "\n");
        std::fflush((FILE*)ev->uData);
    }


    static void Lock()   {
        if (L.lock) { L.lock(true, L.uData); }
    }


    static void unlock() {
        if (L.lock) { L.lock(false, L.uData); }
    }


    const char* LogLevelString(int level) {
        return LevelStrings[level];
    }


    void LogSetLock(LockFn fn, void *uData) {
        L.lock = fn;
        L.uData = uData;
    }


    void LogSetLevel(int level) {
        L.level = level;
    }


    void LogSetQuiet(bool enable) {
        L.quiet = enable;
    }


    int LogAddCallback(LogFn fn, void *uData, int level) {
        for (int i = 0; i < MAX_CALLBACKS; i++) {
            if (!L.callbacks[i].fn) {
                L.callbacks[i].fn = fn;
                L.callbacks[i].uData = uData;
                L.callbacks[i].level = level;
                return 0;
            }
        }
        return -1;
    }


    int LogAddFp(FILE *fp, int level) {
        return LogAddCallback(FileCallback, fp, level);
    }


    static void init_event(LogEvent *ev, void *uData) {
        if (!ev->time) {
            time_t t = time(NULL);
            ev->time = localtime(&t);
        }
        ev->uData = uData;
    }


    void LogLog(int level, const char *file, int line, const char *fmt, ...) {
#if 0
        // To fix(disable) the 'mysterious' crash
        va_list ap;
        va_start(ap, fmt);
        fprintf(stderr, "[%s]\t%s:%d: ", LevelStrings[level]);
        vfprintf(stderr, fmt, ap);
        va_end(ap);
#else
        LogEvent ev = {};
        ev.fmt = fmt;
        ev.file = file;
        ev.line = line;
        ev.level = level;

        Lock();

        if (!L.quiet && level >= L.level) {
            init_event(&ev, stderr);
                    va_start(ev.ap, fmt);
            stdoutCallback(&ev);
                    va_end(ev.ap);
        }

        for (int i = 0; i < MAX_CALLBACKS && L.callbacks[i].fn; i++) {
            Callback *cb = &L.callbacks[i];
            if (level >= cb->level) {
                init_event(&ev, cb->uData);
                        va_start(ev.ap, fmt);
                cb->fn(&ev);
                        va_end(ev.ap);
            }
        }

        unlock();
#endif
    }

    void LogNull()
    {

    }
}