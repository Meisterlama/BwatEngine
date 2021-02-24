#include "ECS/ComponentModel.hpp"


ComponentModel::ComponentModel(Rendering::Model* tmpmodel) 
{
	myModel = tmpmodel;

	myShader = World::GetDefaultShader();
}

ComponentModel::ComponentModel(std::string& pathFile)
{
	Rendering::Model newModel(pathFile);
	myModel = &newModel;

	myShader = World::GetDefaultShader();
}

void ComponentModel::UpdateComponent()
{
	myModel->Draw(*myShader, World::GetWorldLights());
}

