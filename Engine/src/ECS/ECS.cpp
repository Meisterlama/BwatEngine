#include "ECS/ECS.hpp"

#include <random>

#include "Engine.hpp"

#include "ECS/Systems/InputSystem.hpp"
#include "ECS/Systems/PhysicsSystem.hpp"
#include "ECS/Systems/PlayerControlSystem.hpp"
#include "ECS/Systems/RenderSystem.hpp"

#include "ECS/Components/GravityComponent.hpp"
#include "ECS/Components/RigidBodyComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/PlayerComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"

#include "ECS/Coordinator.hpp"


namespace BwatEngine
{
    void InitComponents(Context &context)
    {
        BwatEngine::Coordinator::GetInstance()->RegisterComponent<GravityComponent>();
        BwatEngine::Coordinator::GetInstance()->RegisterComponent<RigidBodyComponent>();
        BwatEngine::Coordinator::GetInstance()->RegisterComponent<CameraComponent>();
        BwatEngine::Coordinator::GetInstance()->RegisterComponent<RenderableComponent>();
        BwatEngine::Coordinator::GetInstance()->RegisterComponent<TransformComponent>();
        BwatEngine::Coordinator::GetInstance()->RegisterComponent<PlayerComponent>();
    }

    void InitSystems(BwatEngine::Context& context)
    {
        context.inputSystem = BwatEngine::Coordinator::GetInstance()->RegisterSystem<InputsSystem>();
        context.inputSystem->Init(context.window.window);

        context.physicsSystem = BwatEngine::Coordinator::GetInstance()->RegisterSystem<PhysicsSystem>();
        {
            Signature signature;
            signature.set(BwatEngine::Coordinator::GetInstance()->GetComponentType<GravityComponent>());
            signature.set(BwatEngine::Coordinator::GetInstance()->GetComponentType<RigidBodyComponent>());
            signature.set(BwatEngine::Coordinator::GetInstance()->GetComponentType<TransformComponent>());
            BwatEngine::Coordinator::GetInstance()->SetSystemSignature<PhysicsSystem>(signature);
        }
        context.physicsSystem->Init();

        context.playerControlSystem = BwatEngine::Coordinator::GetInstance()->RegisterSystem<PlayerControlSystem>();
        {
            Signature signature;
            signature.set(BwatEngine::Coordinator::GetInstance()->GetComponentType<PlayerComponent>());
            signature.set(BwatEngine::Coordinator::GetInstance()->GetComponentType<TransformComponent>());
            BwatEngine::Coordinator::GetInstance()->SetSystemSignature<PlayerControlSystem>(signature);

        }
        context.playerControlSystem->Init();

        context.renderSystem = BwatEngine::Coordinator::GetInstance()->RegisterSystem<RenderSystem>();
        {
            Signature signature;
            signature.set(BwatEngine::Coordinator::GetInstance()->GetComponentType<RenderableComponent>());
            signature.set(BwatEngine::Coordinator::GetInstance()->GetComponentType<TransformComponent>());
            BwatEngine::Coordinator::GetInstance()->SetSystemSignature<RenderSystem>(signature);
        }
        context.renderSystem->Init(&context.window);
    }

    void InitSampleScene(Context &context, Rendering::Model& model)
    {
        std::default_random_engine generator;
        std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
        std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
        std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
        std::uniform_real_distribution<float> randColor(0.0f, 1.0f);
        std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);
        context.entities = std::vector<Entity>(MAX_ENTITIES / 10);
        for (Entity i = 0; i < context.entities.size(); i++)
        {
            context.entities[i] =  BwatEngine::Coordinator::GetInstance()->CreateEntity();
            if (i == 0)
            {
                BwatEngine::Coordinator::GetInstance()->AddComponent<TransformComponent>(context.entities[i], { Math::Transform{
                        Math::Vec3f {0.f, 0.f, 200.f},
                        Math::Vec3f {0.f},
                        Math::Vec3f {1.f}
                } });
                BwatEngine::Coordinator::GetInstance()->AddComponent<CameraComponent>(context.entities[i],
                        { Math::Mat4f::CreatePerspective(80.f, context.window.GetWidth() / context.window.GetHeight(), 0.1f, 1000.0f)
                        });
                BwatEngine::Coordinator::GetInstance()->AddComponent<PlayerComponent>(context.entities[i],{});
                context.renderSystem->SetCamera(context.entities[i]);
            }
            else
            {
                BwatEngine::Coordinator::GetInstance()->AddComponent<GravityComponent>(context.entities[i],{
                                                                   Math::Vec3f{0.f, randGravity(generator), 0.f}
                                                           });
                BwatEngine::Coordinator::GetInstance()->AddComponent<RigidBodyComponent>(context.entities[i],{
                                                                     Math::Vec3f{0.f, 0.f, 0.f},
                                                                     Math::Vec3f{0.f, 0.f, 0.f}
                                                             });
                BwatEngine::Coordinator::GetInstance()->AddComponent<TransformComponent>(context.entities[i],{ Math::Transform{
                        Math::Vec3f{randPosition(generator), randPosition(generator), randPosition(generator)},
                        Math::Vec3f{randRotation(generator), randRotation(generator), randRotation(generator)},
                        Math::Vec3f{3}
                } });
                BwatEngine::Coordinator::GetInstance()->AddComponent<RenderableComponent>(context.entities[i],{ &model });
            }
        }
    }
}