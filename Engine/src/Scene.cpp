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


#include "ECS/Systems/InputSystem.hpp"
#include "ECS/Systems/PhysicsSystem.hpp"
#include "ECS/Systems/PlayerControlSystem.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "Engine.hpp"

#include "Physic/PhysicCast.hpp"
#include "Rendering/Material.hpp"

#include "ResourceManager/ResourceManager.hpp"

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
    : texture("Assets/image/Purple.jpg",Rendering::Texture::Type::E_DIFFUSE), texture1("Assets/image/Heart.png", Rendering::Texture::Type::E_DIFFUSE)
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

    //Rendering::Model mymodel = Rendering::Model{ (std::string) "Assets/bag/backpack.obj" };
    model = Rendering::Model{"Assets/cube.obj" };

    BwatEngine::ResourceManager::Instance()->GetOrLoadModel("Assets/cube.obj");
    BwatEngine::ResourceManager::Instance()->GetOrLoadModel("Assets/sphere.obj");
    BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/Heart.png", Rendering::Texture::Type::E_DIFFUSE);
    BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/Purple.jpg", Rendering::Texture::Type::E_DIFFUSE);

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
                statActor->userData = (void*)0x1234;
                /*ColliderComponent& collider = */coordinator.AddComponent<ColliderComponent>(entities[i],{ material, physx::PxBoxGeometry{ ToPxVec3(eTransform.scale / 2.f) } });
                coordinator.AddComponent<RenderableComponent>(entities[i],{ &model });

                coordinator.GetComponent<StaticActorComponent>(entities[i]).staticActor->attachShape(
                    *coordinator.GetComponent<ColliderComponent>(entities[i]).shape);

                scenePhysic->addActor(*statActor);

                auto& renderableComponent = coordinator.GetComponent<RenderableComponent>(entities[i]);
                renderableComponent.materials[0] = &myMat;
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

                //physx::PxActor* actor = coordinator.GetComponent<ColliderComponent>().staticActorentities[i],;
                coordinator.GetComponent<RigidBodyComponent>(entities[i]).rigidBody->attachShape(
                    *coordinator.GetComponent<ColliderComponent>(entities[i]).shape);
                //actor->userData = (void*)0x1234;
                scenePhysic->addActor(*coordinator.GetComponent<RigidBodyComponent>(entities[i]).rigidBody);

                auto& renderableComponent = coordinator.GetComponent<RenderableComponent>(entities[i]);
                renderableComponent.materials[0] = &myMat1;

            }
        }
}