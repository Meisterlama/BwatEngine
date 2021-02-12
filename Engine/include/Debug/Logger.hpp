#ifndef DEBUG_LOGGER_HPP
#define DEBUG_LOGGER_HPP


//for the first one
#include <fstream>
#include <string>
#include <mutex>


// for the snd one
#include <cstdio>
#include <cstdarg>
#include <cstdbool>
#include <ctime>

namespace BLogger
{
#if 0
    //the first log try

    class Log
    {
    public:
        // Constructor with Parameter
        Log(std::string fileName);

        // disable the copy for the constructor and assignment
        Log(const Log&) = delete;
        Log& operator=(const Log&) = delete;

        // create a move for the constructor and assignment
        Log(Log&& other)
        {
            myStream.close();
            myStream = move(other.myStream);
        }

        Log& operator=(Log&& other)
        {
            myStream.close();
            myStream = move(other.myStream);

            return *this;
        }


        // Destructor
        ~Log()
        {
         myStream.close();
        }

        // Write in the logFile
        void WriteLine(std::string content);

    private:
        std::ofstream myStream;
        std::mutex myMutex;
    };

#else
    //the second logger class that can be used

    typedef struct {
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

#define LogTrace(...) LogLog(BLogger::E_LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__ )
#define LogDebug(...) LogLog(BLogger::E_LOG_DEBUG, __FILE__, __LINE__, _VA_ARGS_ )
#define LogInfo(...) LogLog(BLogger::E_LOG_INFO, __FILE__, __LINE__, __VA_ARGS__ )
#define LogWarn(...) LogLog(BLogger::E_LOG_WARN, __FILE__, __LINE__, __VA_ARGS__ )
#define LogError(...) LogLog(BLogger::E_LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__ )
#define LogFatal(...) LogLog(BLogger::E_LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__ )

    const char* LogLevelString(int level);
    void LogSetLock(LockFn fn, void *uData);
    void LogSetLevel(int level);
    void LogSetQuiet(bool enable);
    int LogAddCallback(LogFn, void* uData, int level);
    int LogAddFp(FILE *fp, int level);

    void LogLog(int level, const char*file, int line, const char *fmt, ...);


#endif
}


#endif