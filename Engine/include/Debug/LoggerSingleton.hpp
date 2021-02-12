#ifndef DEBUG_LOGGERSINGLETON_HPP
#define DEBUG_LOGGERSINGLETON_HPP

#include "Logger.hpp"


#if 0
namespace BLogger
{
    class LoggerSingleton
    {
    public:
        LoggerSingleton(LoggerSingleton const&) = delete;
        LoggerSingleton(LoggerSingleton&&) = delete;
        LoggerSingleton& operator=(LoggerSingleton const&) = delete;
        LoggerSingleton& operator=(LoggerSingleton&&) = delete;

        static Log& Instance()
        {
            static Log myInstance(R"(Log.txt)");
            return myInstance;
        }

    protected:
        LoggerSingleton() {}
        ~LoggerSingleton() {}

    };
}
#endif

#endif