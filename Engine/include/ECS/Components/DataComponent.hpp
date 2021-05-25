#ifndef BWATENGINE_DATACOMPONENT_H
#define BWATENGINE_DATACOMPONENT_H

#include "ECS/Coordinator.hpp"

namespace BwatEngine
{
    struct DataComponent
    {
        std::string name;

        DataComponent(std::string _name = "")
        {
            if (_name.empty())
            {
                name = "CHANGE_ME";
            }
            else
            {
                name = _name;
            }
        }
    };
}

#endif //BWATENGINE_DATACOMPONENT_H
