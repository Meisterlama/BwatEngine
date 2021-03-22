#include "Scene.hpp"

#include "Inputs/InputHandler.hpp"
#include "ECS/Components/GravityComponent.hpp"
#include "ECS/Components/RigidBodyComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/PlayerComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/ColliderComponent.hpp"


#include "ECS/Systems/InputSystem.hpp"
#include "ECS/Systems/PhysicsSystem.hpp"
#include "ECS/Systems/PlayerControlSystem.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "Engine.hpp"

#include "Physic/PhysicCast.hpp"


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
{
    Entity::InitCoordinator();
    Entity::GetCoordinator().RegisterComponent<GravityComponent>();
    Entity::GetCoordinator().RegisterComponent<RigidBodyComponent>();
    Entity::GetCoordinator().RegisterComponent<CameraComponent>();
    Entity::GetCoordinator().RegisterComponent<RenderableComponent>();
    Entity::GetCoordinator().RegisterComponent<TransformComponent>();
    Entity::GetCoordinator().RegisterComponent<PlayerComponent>();
    Entity::GetCoordinator().RegisterComponent<ColliderComponent>();

    inputSystem = Entity::GetCoordinator().RegisterSystem<InputsSystem>();
    inputSystem->Init(window);

    physicsSystem = Entity::GetCoordinator().RegisterSystem<PhysicsSystem>();
    {
        Signature signature;
        signature.set(Entity::GetComponentType<RigidBodyComponent>());
        signature.set(Entity::GetComponentType<TransformComponent>());
        signature.set(Entity::GetComponentType<ColliderComponent>());
        Entity::GetCoordinator().SetSystemSignature<PhysicsSystem>(signature);
    }
    physicsSystem->Init(this, {0, -1, 0});

    playerControlSystem = Entity::GetCoordinator().RegisterSystem<PlayerControlSystem>();
    {
        Signature signature;
        signature.set(Entity::GetComponentType<PlayerComponent>());
        signature.set(Entity::GetComponentType<TransformComponent>());
        Entity::GetCoordinator().SetSystemSignature<PlayerControlSystem>(signature);

    }
    playerControlSystem->Init();

    renderSystem = Entity::GetCoordinator().RegisterSystem<RenderSystem>();
    {
        Signature signature;
        signature.set(Entity::GetComponentType<RenderableComponent>());
        signature.set(Entity::GetComponentType<TransformComponent>());
        Entity::GetCoordinator().SetSystemSignature<RenderSystem>(signature);
    }
    renderSystem->Init();

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

        for (EntityType i = 0; i < entities.size(); i++)
        {
            if (i == 0)
            {
                entities[i].AddComponent<TransformComponent>({ Math::Transform{
                    Math::Vec3f {0.f, 0.f, 200.f},
                    Math::Vec3f {0.f},
                    Math::Vec3f {1.f}
                } });
                entities[i].AddComponent<CameraComponent>(
                    { Math::Mat4f::CreatePerspective(80.f, 
                        window.GetWidth() / window.GetHeight(), 0.1f, 1000.0f)
                    });
                entities[i].AddComponent<PlayerComponent>({});
                entities[i].name = "Camera";
                renderSystem->SetCamera(&entities[i]);
            }
            else
            {               
                entities[i].AddComponent<TransformComponent>({ Math::Transform{
                    Math::Vec3f{randPosition(generator), randPosition(generator), randPosition(generator)},
                    Math::Vec3f{randRotation(generator), randRotation(generator), randRotation(generator)},
                    Math::Vec3f{3}
                } });
                auto& eTransform =  entities[i].GetComponent<TransformComponent>().transform;
                entities[i].AddComponent<RigidBodyComponent>(eTransform);
                entities[i].AddComponent<ColliderComponent>({ material, physx::PxBoxGeometry{ ToPxVec3(eTransform.scale / 2) }, eTransform });
                entities[i].AddComponent<RenderableComponent>({ &model });

                //physx::PxActor* actor = entities[i].GetComponent<ColliderComponent>().staticActor;
                //actor->userData = (void*)0x1234;
                scenePhysic->addActor(*entities[i].GetComponent<RigidBodyComponent>().rigidBody);
            }
        }
}