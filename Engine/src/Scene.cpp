#include "Scene.hpp"

#include "ECS/Coordinator.hpp"
#include "ECS/Components/RigidBodyComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/ColliderComponent.hpp"
#include "ECS/Components/ScriptComponent.hpp"
#include "ECS/Components/AudioSourceComponent.hpp"
#include "ECS/Components/LightComponent.hpp"
#include "ECS/Components/DataComponent.hpp"
#include "ECS/Components/AnimatorComponent.hpp"

#include "ECS/Systems/PhysicsSystem.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Systems/SoundSystem.hpp"
#include "ECS/Systems/ScriptSystem.hpp"
#include "ECS/Systems/PostProcessSystem.hpp"
#include "ECS/Systems/AnimationSystem.hpp"


using namespace BwatEngine;

Scene::Scene(Window& window)
{
    scenePhysic.Init(physic);



    Coordinator& coordinator = Coordinator::GetInstance();

    coordinator.RegisterComponent<RigidBodyComponent>();
    coordinator.RegisterComponent<CameraComponent>();
    coordinator.RegisterComponent<RenderableComponent>();
    coordinator.RegisterComponent<TransformComponent>();
    coordinator.RegisterComponent<ColliderComponent>();
    coordinator.RegisterComponent<ScriptComponent>();
    coordinator.RegisterComponent<AudioSourceComponent>();
    coordinator.RegisterComponent<LightComponent>();
    coordinator.RegisterComponent<DataComponent>();
    coordinator.RegisterComponent<AnimatorComponent>();
    coordinator.RegisterComponent<ListenerComponent>();

    coordinator.RegisterSystem<PhysicsSystem>(&scenePhysic);
    coordinator.SetSystemSignature<PhysicsSystem, RigidBodyComponent, TransformComponent, ColliderComponent>();
    coordinator.SetSystemConfig<PhysicsSystem>(SystemConfig{SystemConfig::GameUpdate, 2});

    coordinator.RegisterSystem<RenderSystem>(window.GetWidth(), window.GetHeight());
    coordinator.SetSystemSignature<RenderSystem, RenderableComponent, TransformComponent>();
    coordinator.SetSystemConfig<RenderSystem>(SystemConfig{SystemConfig::ManualUpdate});


    // =================================== SCRIPT =================================== //

    coordinator.RegisterSystem<ScriptSystem>();
    coordinator.SetSystemSignature<ScriptSystem, ScriptComponent>();
    coordinator.SetSystemConfig<ScriptSystem>(SystemConfig{SystemConfig::GameUpdate, 1});

    // =================================== SOUND =================================== //
    coordinator.RegisterSystem<SoundSystem>();
    coordinator.SetSystemSignature<SoundSystem, AudioSourceComponent, TransformComponent>();
    coordinator.SetSystemConfig<SoundSystem>(SystemConfig{SystemConfig::GameUpdate});

    // =================================== POST PROCESS =================================== //
    coordinator.RegisterSystem<PostProcessSystem>(window.GetWidth(), window.GetHeight());
    coordinator.SetSystemConfig<PostProcessSystem>(SystemConfig{SystemConfig::ManualUpdate});

    // ===================================  ANIMATION  =================================== //
    coordinator.RegisterSystem<AnimationSystem>();
    coordinator.SetSystemSignature<AnimationSystem, RenderableComponent, AnimatorComponent>();
    coordinator.SetSystemConfig<AnimationSystem>(SystemConfig{ SystemConfig::AlwaysUpdate });
}