#ifndef _PRIMITIVES_HPP_
#define _PRIMITIVES_HPP_

#include "Rendering/Model.hpp"

Rendering::Model CreateCube();
Rendering::Model CreateSphere(int latitudeCount = 20, int longitudeCount = 20);
Rendering::Model CreatePlan();

#endif // _PRIMITIVES_HPP_