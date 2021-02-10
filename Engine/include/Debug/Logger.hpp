#ifndef DEBUG_LOGGER_HPP
#define DEBUG_LOGGER_HPP

#include <fstream>
#include <string>
#include <mutex>

namespace BLogger
{
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
}


#endif