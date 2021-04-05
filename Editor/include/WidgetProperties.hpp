#ifndef BWATENGINE_WIDGETPROPERTIES_H
#define BWATENGINE_WIDGETPROPERTIES_H

#include "Widget.hpp"
#include <memory>
#include "Core.hpp"
#include <ECS/Components/TransformComponent.hpp>

class WidgetProperties : public Widget
{
public:
    WidgetProperties(EditorInterface* editor);

    void TickVisible() override;

    static void Inspect(BwatEngine::Entity& entity);

		// It's actually okay however it limits the editor to
		// one entity, it's a pity as there is no interest in
		// doing so
    static BwatEngine::Entity currentEntity;

private:
		// Where are the definitions ?
		// https://stackoverflow.com/questions/115703/storing-c-template-function-definitions-in-a-cpp-file
    
		// I don't understand why you are not creating a widget for each component
		// it will be way simpler to maintain
		template<typename T>
    void ShowComponent(T& component);

    template<typename T>
    bool AddComponentMenuItem(BwatEngine::Entity entity);

    template<typename T>
    bool ShowComponentMenuItem(BwatEngine::Entity entity);

};

#endif //BWATENGINE_WIDGETPROPERTIES_H
