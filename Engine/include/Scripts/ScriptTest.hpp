#ifndef SCRIPT_TEST_HPP
#define SCRIPT_TEST_HPP

#include "ECS/Components/ScriptComponent.hpp"

class ScriptTest : public Script
{

public:

	virtual void Update() override;
	virtual void Start() override;
	

private:

	float timer = 5.f ;
	float initTImer = 5.f;
};

#endif // !1
