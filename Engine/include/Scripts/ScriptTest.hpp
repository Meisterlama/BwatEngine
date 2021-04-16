#ifndef SCRIPT_TEST_HPP
#define SCRIPT_TEST_HPP

#include "ECS/Components/ScriptComponent.hpp"
#include "Physic/RigidBody.hpp"

namespace BwatEngine
{

	class ScriptTest : public Script
	{

	public:

		virtual void Update() override;
		virtual void Start() override;

		void OnCollisionEnter(RigidBody& other) ;


	private:

		float timer = 5.f;
		float initTImer = 5.f;
	};
}

#endif // !1
