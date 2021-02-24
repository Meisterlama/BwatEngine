#ifndef COMPONENTMODEL_HPP
#define COMPONENTMODEL_HPP

#include "ECS/Component.hpp"
#include "Rendering/model.hpp"
#include "World.hpp"

class ComponentModel : public Component
{

private:
	
	Rendering::Shader* myShader;
	Rendering::Model* myModel;

public:

	ComponentModel(std::string& pathFile);
	void UpdateComponent() override;

};

#endif // !COMPONENTMODEL_HPP