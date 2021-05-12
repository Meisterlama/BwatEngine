#include "Scene.hpp"

#include "Math/Misc/RNG.hpp"

#include "ECS/Coordinator.hpp"
#include "ECS/Components/RigidBodyComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/PlayerComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/ColliderComponent.hpp"
#include "ECS/Components/ScriptComponent.hpp"
#include "ECS/Components/AudioSourceComponent.hpp"
#include "ECS/Components/LightComponent.hpp"
#include "ECS/Components/DataComponent.hpp"

#include "ECS/Systems/PhysicsSystem.hpp"
#include "ECS/Systems/PlayerControlSystem.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Systems/SoundSystem.hpp"
#include "ECS/Systems/ScriptSystem.hpp"
#include "ECS/Systems/PostProcessSystem.hpp"

#include "ResourceManager/ResourceManager.hpp"

using namespace BwatEngine;

Scene::Scene(Window& window)
    : texture(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/brickwall.jpg",Rendering::Texture::Type::E_DIFFUSE)), texture1(BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/green.png", Rendering::Texture::Type::E_DIFFUSE))
{
    scenePhysic.Init(physic);



    Coordinator& coordinator = Coordinator::GetInstance();

    coordinator.RegisterComponent<RigidBodyComponent>();
    coordinator.RegisterComponent<CameraComponent>();
    coordinator.RegisterComponent<RenderableComponent>();
    coordinator.RegisterComponent<TransformComponent>();
    coordinator.RegisterComponent<PlayerComponent>();
    coordinator.RegisterComponent<ColliderComponent>();
    coordinator.RegisterComponent<ScriptComponent>();
    coordinator.RegisterComponent<AudioSourceComponent>();
    coordinator.RegisterComponent<LightComponent>();
    coordinator.RegisterComponent<DataComponent>();

    physicsSystem = coordinator.RegisterSystem<PhysicsSystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentType<RigidBodyComponent>());
        signature.set(coordinator.GetComponentType<TransformComponent>());
        signature.set(coordinator.GetComponentType<ColliderComponent>());
        coordinator.SetSystemSignature<PhysicsSystem>(signature);
    }
    physicsSystem->Init(&scenePhysic);

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

    // =================================== SCRIPT =================================== //

    scriptSystem = coordinator.RegisterSystem<ScriptSystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentType<ScriptComponent>());
        coordinator.SetSystemSignature<ScriptSystem>(signature);
    }
    scriptSystem->Init();

    // =================================== SOUND =================================== //
    soundSystem = coordinator.RegisterSystem<SoundSystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentType<AudioSourceComponent>());
        coordinator.SetSystemSignature<SoundSystem>(signature);
    }
    soundSystem->Init();

    // =================================== POST PROCESS =================================== //
    postProcessSystem = coordinator.RegisterSystem<PostProcessSystem>(window.GetWidth(), window.GetHeight());




    //Rendering::Model mymodel = Rendering::Model{ (std::string) "Assets/bag/backpack.obj" };
    model = BwatEngine::ResourceManager::Instance()->GetOrLoadModel("Assets/cube.obj");;
    

    //BwatEngine::ResourceManager::Instance()->GetOrLoadModel("Assets/sphere.obj");
    BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/green.png", Rendering::Texture::Type::E_DIFFUSE);
    BwatEngine::ResourceManager::Instance()->GetOrLoadTexture("Assets/image/moteur.jpg", Rendering::Texture::Type::E_DIFFUSE);
    Audio::AudioData* audioData = BwatEngine::ResourceManager::Instance()->GetOrLoadAudio("Assets/pop.wav");

    Math::RNG randPosition{0};  //(-100.0f, 100.0f);
    Math::RNG randRotation{1};  //(0.0f, 3.0f);

    physx::PxMaterial* material = Physic::GetPhysics()->createMaterial(0,0,0);

    myMat.SetDiffuse(*texture);
    myMat1.SetDiffuse(*texture1);
    
        for (int i = 0; i < 10 ; i++)
        {
            auto entity = coordinator.CreateEntity();
            if (i == 0)
            {
                coordinator.AddComponent<TransformComponent>(entity,
                    Math::Vec3f{0.f, 0.f, 200.f},
                     Math::Vec3f{0.f},
                     Math::Vec3f{1.f}
                    );
                coordinator.AddComponent<CameraComponent>(entity, {});
                coordinator.AddComponent<PlayerComponent>(entity, {});
//                renderSystem->SetCamera(entity);
            }
            else if (i == 1) // ================================= Plane
            {
                coordinator.AddComponent<TransformComponent>(entity,
                    Math::Vec3f{0, -11, 0},
                    Math::Vec3f{0, 0, 0},
                    Math::Vec3f{300, 1, 300});

                auto eTransform = coordinator.GetComponent<TransformComponent>(entity);
                coordinator.AddComponent<RigidBodyComponent>(entity, eTransform , true);

                coordinator.AddComponent<ColliderComponent>(entity, { new BoxCollider{eTransform.scale} });
                coordinator.AddComponent<RenderableComponent>(entity,{ model });

                auto& renderableComponent = coordinator.GetComponent<RenderableComponent>(entity);
                renderableComponent.materials[0] = &myMat;

            }
            else if ( i == 2 )// ================================= Cube
            {
                coordinator.AddComponent<LightComponent>(entity, {});
            }
            else
            {
                coordinator.AddComponent<TransformComponent>(entity,

                    Math::Vec3f{
                        randPosition.RollRandomFloatInRange(0.f, 30.f),
                        randPosition.RollRandomFloatInRange(0.f, 30.f),
                        randPosition.RollRandomFloatInRange(0.f, 30.f)
                        },
                    Math::Vec3f{
                        randPosition.RollRandomFloatInRange(0.f, 3.f),
                        randPosition.RollRandomFloatInRange(0.f, 3.f),
                        randPosition.RollRandomFloatInRange(0.f, 3.f)
                        },
                    Math::Vec3f{3});

                auto eTransform = coordinator.GetComponent<TransformComponent>(entity);
                coordinator.AddComponent<RigidBodyComponent>(entity, eTransform);

                coordinator.AddComponent<ColliderComponent>(entity, { new SphereCollider{eTransform.scale.X} });
                coordinator.AddComponent<RenderableComponent>(entity, { model });

                auto& renderableComponent = coordinator.GetComponent<RenderableComponent>(entity);
                renderableComponent.materials[0] = new Rendering::Material;
                renderableComponent.materials[0]->diffuse = texture1;

                coordinator.AddComponent<AudioSourceComponent>(entity, AudioSourceComponent{*audioData});
                coordinator.AddComponent<ScriptComponent>(entity, "Assets/script/update.lua");

            }
        }
}