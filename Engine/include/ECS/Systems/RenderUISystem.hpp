#ifndef RENDERUISYSTEM_HPP
#define RENDERUISYSTEM_HPP

#include "ECS/System.hpp"
#include "ECS/ECS.hpp"


#include "Rendering/RenderUI.hpp"

namespace BwatEngine
{

    class RenderUISystem : public System
    {
    private:
        Rendering::Quad quad;
    public:

        RenderUISystem();
        virtual void Update() override;

    };
}


#endif // RENDERUISYSTEM_HPP
