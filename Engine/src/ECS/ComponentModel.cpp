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
                      BwatEngine::Math::Mat4f::CreateXYZRotationMat(transform.rotation).Transpose() *
                      BwatEngine::Math::Mat4f::CreateTranslationMat(transform.position) *
                      BwatEngine::Math::Mat4f::CreateScaleMat(transform.scale)
                      );
	myModel->Draw(*myShader, World::GetWorldLights());
}

