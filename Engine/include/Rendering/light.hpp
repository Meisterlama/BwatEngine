#pragma once

#include "../Math/Vec3.h"
#include "shader.hpp"


class Light
{
private:
    
public:
    Vec3 position{0,0,0};
    Vec3 direction{0,0,0};

    // classic
    Vec3 ambient{0,0,0};
    Vec3 diffuse{0,0,0};
    Vec3 specular{ 0,0,0 };

   
    Light();
    ~Light();

    //Methods

};

