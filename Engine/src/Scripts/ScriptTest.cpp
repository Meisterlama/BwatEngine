#include "Scripts/ScriptTest.hpp"
#include "Time.hpp"
#include "Debug/Logger.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/RigidBodyComponent.hpp"

using namespace BwatEngine;

void ScriptTest::OnCollisionEnter(RigidBody& other)
{
	other.SetVelocity({ 0,50,0 });

	LogInfo("je suis dans ma collision t'es dans ta soumision ! ");
}

void ScriptTest::Start()
{
	Coordinator& coordinator = *Coordinator::GetInstance();

	rb = coordinator.GetComponent<RigidBodyComponent>(entity).rigidBody;

	rb->setContactFunc(COLLISION_TYPE::OnEnterCollision, [this](RigidBody& rb) {this->OnCollisionEnter(rb); });
}

void ScriptTest::Update()
{
	
}

