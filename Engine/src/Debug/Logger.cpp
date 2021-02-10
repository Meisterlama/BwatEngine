#include "Debug/Logger.hpp"

#include <ctime>

namespace BLogger
{
    Log::Log(std::string fileName)
    {
        myStream.open(fileName);

        if (myStream.fail())
            throw std::iostream::failure("Cannot open file: " + fileName);
    }

    void Log::WriteLine(std::string content)
    {
        std::lock_guard<std::mutex> lock(myMutex);

        std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        char timestamp[26];
        ctime_s(timestamp, sizeof timestamp, &now);

        std::string timestampNoEndl(timestamp);
        timestampNoEndl = timestampNoEndl.substr(0,24);

        myStream << timestampNoEndl << ": " << content << std::endl;

    }
}