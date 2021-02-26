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
	Transform transform = this->GetParent()->GetTransform();
	myShader->setMat4("model",
                      BMath::Matrix4<float>::CreateXYZRotationMat(transform.rotation).Transpose() *
                      BMath::Matrix4<float>::CreateTranslationMat(transform.position) *
                      BMath::Matrix4<float>::CreateScaleMat(transform.scale)
                      );
	myModel->Draw(*myShader, World::GetWorldLights());
}

