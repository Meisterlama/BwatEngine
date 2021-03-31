#include "Scene.hpp"

#include "Inputs/InputHandler.hpp"

#include "ECS/Coordinator.hpp"
#include "ECS/Components/GravityComponent.hpp"
#include "ECS/Components/RigidBodyComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/PlayerComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/ColliderComponent.hpp"
#include "ECS/Components/StaticActorComponent.hpp"
#include "ECS/Components/ScriptComponent.hpp"


#include "ECS/Systems/InputSystem.hpp"
#include "ECS/Systems/PhysicsSystem.hpp"
#include "ECS/Systems/PlayerControlSystem.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Systems/ScriptSystem.hpp"
#include "Engine.hpp"

#include "Physic/PhysicCast.hpp"
#include "Rendering/Material.hpp"

// Script include 
#include "Scripts/ScriptTest.hpp"

//#include "Rendering/Material.hpp"


using namespace BwatEngine;

std::vector<Rendering::Light> Scene::lights;

void Scene::AddLight(Rendering::Light& newlight)
{
	lights.push_back(newlight);
}

std::vector<Rendering::Light>& Scene::GetLights()
{
	return lights;
}

Scene::Scene(Window& window)
    : texture("Assets/image/green.png",Rendering::Texture::Type::E_DIFFUSE), texture1("Assets/image/moteur.jpg", Rendering::Texture::Type::E_DIFFUSE)
{
    Coordinator& coordinator = *Coordinator::GetInstance();
    coordinator.Init();

    coordinator.RegisterComponent<GravityComponent>();
    coordinator.RegisterComponent<RigidBodyComponent>();
    coordinator.RegisterComponent<CameraComponent>();
    coordinator.RegisterComponent<RenderableComponent>();
    coordinator.RegisterComponent<TransformComponent>();
    coordinator.RegisterComponent<PlayerComponent>();
    coordinator.RegisterComponent<ColliderComponent>();
    coordinator.RegisterComponent<StaticActorComponent>();
    coordinator.RegisterComponent<ScriptComponent>();


    inputSystem = coordinator.RegisterSystem<InputsSystem>();
    inputSystem->Init(window);

    physicsSystem = coordinator.RegisterSystem<PhysicsSystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentType<RigidBodyComponent>());
        signature.set(coordinator.GetComponentType<TransformComponent>());
        signature.set(coordinator.GetComponentType<ColliderComponent>());
        coordinator.SetSystemSignature<PhysicsSystem>(signature);
    }
    physicsSystem->Init(this, { 0, -10, 0 });

    playerControlSystem = coordinator.RegisterSystem<PlayerControlSystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentType<PlayerComponent>());
        signature.set(coordinator.GetComponentType<TransformComponent>());
        coordinator.SetSystemSignature<PlayerControlSystem>(signature);

    }
    playerControlSystem->Init();

    renderSystem = coordinator.RegisterSystem<RenderSystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentType<RenderableComponent>());
        signature.set(coordinator.GetComponentType<TransformComponent>());
        coordinator.SetSystemSignature<RenderSystem>(signature);
    }
    renderSystem->Init();

    // =================================== SCRIPT =================================== //

    scriptSystem = coordinator.RegisterSystem<ScriptSystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentType<ScriptComponent>());
        coordinator.SetSystemSignature<ScriptSystem>(signature);
    }
    scriptSystem->Init();

    //Rendering::Model mymodel = Rendering::Model{ (std::string) "Assets/bag/backpack.obj" };
    model = Rendering::Model{ (std::string) "Assets/cube.obj" };

    std::default_random_engine generator;
    std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
    std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
    std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
    std::uniform_real_distribution<float> randColor(0.0f, 1.0f);
    std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);

    physx::PxMaterial* material = Physic::GetPhysics()->createMaterial(0,0,0);

    entities = std::vector<Entity>(MAX_ENTITIES);
    
    myMat.SetDiffuse(texture);
    myMat1.SetDiffuse(texture1);
    
        for (Entity i = 0; i < entities.size(); i++)
        {
            entities[i] = coordinator.CreateEntity();
            if (i == 0)
            {
                coordinator.AddComponent<TransformComponent>(entities[i],{ Math::Transform{
                    Math::Vec3f {0.f, 0.f, 200.f},
                    Math::Vec3f {0.f},
                    Math::Vec3f {1.f}
                } });
                coordinator.AddComponent<CameraComponent>(entities[i],
                    { Math::Mat4f::CreatePerspective(80.f,
                        window.GetWidth() / window.GetHeight(), 0.1f, 1000.0f)
                    });
                coordinator.AddComponent<PlayerComponent>(entities[i], {});
                renderSystem->SetCamera(entities[i]);
            }
            else if (i == 1) // Plane
            {
                coordinator.AddComponent<TransformComponent>(entities[i],{ Math::Transform{
                    Math::Vec3f{0, -105, 0},
                    Math::Vec3f{0, 0, 0},
                    Math::Vec3f{300, 1, 300}} });

                Math::Transform& eTransform = coordinator.GetComponent<TransformComponent>(entities[i]).transform;
                coordinator.AddComponent<StaticActorComponent>(entities[i],eTransform);

                auto& statActor = coordinator.GetComponent<StaticActorComponent>(entities[i]).staticActor;
                coordinator.AddComponent<ColliderComponent>(entities[i],{ material, physx::PxBoxGeometry{ ToPxVec3(eTransform.scale / 2.f) } });
                coordinator.AddComponent<RenderableComponent>(entities[i],{ &model });

                coordinator.GetComponent<StaticActorComponent>(entities[i]).staticActor->attachShape(
                    *coordinator.GetComponent<ColliderComponent>(entities[i]).shape);

                scenePhysic->addActor(*statActor);

                auto& renderableComponent = coordinator.GetComponent<RenderableComponent>(entities[i]);
                renderableComponent.materials[0] = &myMat;

                ScriptTest* monScript = new ScriptTest;
                coordinator.AddComponent<ScriptComponent>(entities[i], { monScript });
            }
            else // Cube
            {
                coordinator.AddComponent<TransformComponent>(entities[i],{ Math::Transform{
                    Math::Vec3f{randPosition(generator), randPosition(generator), randPosition(generator)},
                    Math::Vec3f{randRotation(generator), randRotation(generator), randRotation(generator)},
                    Math::Vec3f{3}
                } });
                auto& eTransform = coordinator.GetComponent<TransformComponent>(entities[i]).transform;
                coordinator.AddComponent<RigidBodyComponent>(entities[i],eTransform);
                coordinator.AddComponent<ColliderComponent>(entities[i],{ material, physx::PxBoxGeometry{ ToPxVec3(eTransform.scale / 2) }, eTransform });
                coordinator.AddComponent<RenderableComponent>(entities[i],{ &model });

                coordinator.GetComponent<RigidBodyComponent>(entities[i]).rigidBody->attachShape(
                *coordinator.GetComponent<ColliderComponent>(entities[i]).shape);
                scenePhysic->addActor(*coordinator.GetComponent<RigidBodyComponent>(entities[i]).rigidBody);

                auto& renderableComponent = coordinator.GetComponent<RenderableComponent>(entities[i]);
                renderableComponent.materials[0] = &myMat1;

            }
        }
}