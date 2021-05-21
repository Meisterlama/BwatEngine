#ifndef TYPE_HPP
#define TYPE_HPP

//from https://stackoverflow.com/questions/281818/

#include <string>
#include <typeinfo>

namespace BwatEngine::ECS::Internal
{
    std::string demangle(const char *name);
}

#endif
