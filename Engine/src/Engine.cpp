#include "Engine.hpp"

#include <random>

#include "Math/Math.hpp"
#include "ECS/Entity.hpp"

#include "Rendering/Shader.hpp"
#include "Rendering/Camera.hpp"
#include "EditorInterface.hpp"
#include "Rendering/Light.hpp"
#include "World.hpp"

#include "Inputs/InputHandler.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Components/GravityComponent.hpp"
#include "ECS/Components/RigidBodyComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/PlayerComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"


#include "ECS/Systems/InputSystem.hpp"
#include "ECS/Systems/PhysicsSystem.hpp"
#include "ECS/Systems/PlayerControlSystem.hpp"
#include "ECS/Systems/RenderSystem.hpp"

namespace BwatEngine {

    //initialization
    Engine::Engine()
    {
        //Window mainWindow;
        

        // Init ImGui
        /*IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(mainWindow.window, true);
        ImGui_ImplOpenGL3_Init("#version 330");*/

        Entity::InitCoordinator();
        Entity::GetCoordinator().RegisterComponent<GravityComponent>();
        Entity::GetCoordinator().RegisterComponent<RigidBodyComponent>();
        Entity::GetCoordinator().RegisterComponent<CameraComponent>();
        Entity::GetCoordinator().RegisterComponent<RenderableComponent>();
        Entity::GetCoordinator().RegisterComponent<TransformComponent>();
        Entity::GetCoordinator().RegisterComponent<PlayerComponent>();

        inputSystem = Entity::GetCoordinator().RegisterSystem<InputsSystem>();
        inputSystem->Init(window.window);

        physicsSystem = Entity::GetCoordinator().RegisterSystem<PhysicsSystem>();
        {
            Signature signature;
            signature.set(Entity::GetComponentType<GravityComponent>());
            signature.set(Entity::GetComponentType<RigidBodyComponent>());
            signature.set(Entity::GetComponentType<TransformComponent>());
            Entity::GetCoordinator().SetSystemSignature<PhysicsSystem>(signature);
        }
        physicsSystem->Init();

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
        renderSystem->Init(&window);


        // time init var

        //Rendering::Model mymodel = Rendering::Model{ (std::string) "Assets/bag/backpack.obj" };
        model = Rendering::Model{ (std::string) "Assets/cube.obj" };

        std::vector<Entity> entities(MAX_ENTITIES);

        std::default_random_engine generator;
        std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
        std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
        std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
        std::uniform_real_distribution<float> randColor(0.0f, 1.0f);
        std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);


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
                    { Math::Mat4f::CreatePerspective(80.f, window.GetWidth() / window.GetHeight(), 0.1f, 1000.0f)
                    });
                entities[i].AddComponent<PlayerComponent>({});
                entities[i].name = "Camera";
                renderSystem->SetCamera(&entities[i]);
            }
            else
            {
                entities[i].AddComponent<GravityComponent>({
                                                               Math::Vec3f{0.f, randGravity(generator), 0.f}
                    });
                entities[i].AddComponent<RigidBodyComponent>({
                                                                 Math::Vec3f{0.f, 0.f, 0.f},
                                                                 Math::Vec3f{0.f, 0.f, 0.f}
                    });
                entities[i].AddComponent<TransformComponent>({ Math::Transform{
                    Math::Vec3f{randPosition(generator), randPosition(generator), randPosition(generator)},
                    Math::Vec3f{randRotation(generator), randRotation(generator), randRotation(generator)},
                    Math::Vec3f{3}
                } });
                entities[i].AddComponent<RenderableComponent>({ &model });
            }
        }

    }

    Engine::~Engine()
    {
    }

    //Main Funtion of engine 
    void Engine::Update()
    {
        while (window.IsWorking())
        {
            glfwPollEvents();

            //Time
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;


            //ImGui
            /*ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            //ImGui::ShowDemoWindow();

            ImGui::Text("FPS: %f", (deltaTime !=0) ? 1/deltaTime : 0);

            ImGui::ColorEdit3("Clear color", renderSystem->clearColor.values);
            //debug Light
            ImGui::ColorEdit3("light ambient", World::GetWorldLights()[0].ambient.values);
            static int item_current = 0;

            ImGui::ListBoxHeader("Entities");
            for (EntityType i = 0; i < entities.size(); i++)
            {
                bool selected = false;
                std::string entityName = (entities[i].name != "")?entities[i].name  : "Entity_" + std::to_string(entities[i].GetID());

                if (ImGui::Selectable(entityName.c_str()))
                {
                    item_current = i;
                }
            }
            ImGui::ListBoxFooter();


            ImGui::DragFloat3("position", entities[item_current].GetComponent<TransformComponent>().transform.position.values, 0.01);
            ImGui::DragFloat3("rotation", entities[item_current].GetComponent<TransformComponent>().transform.rotation.values, 0.01);
            ImGui::DragFloat3("scale", entities[item_current].GetComponent<TransformComponent>().transform.scale.values, 0.01);*/


            //physicsSystem->Update(deltaTime);
            playerControlSystem->Update(deltaTime, window);
            renderSystem->Update(deltaTime);
            inputSystem->Update(deltaTime);

            //ImGui::Render();
            //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window.window);
        }
    }


    //Close all content 
    void Engine::Close()
    {

        //ImGui_ImplGlfw_Shutdown();
        //ImGui_ImplOpenGL3_Shutdown();
        //ImGui::DestroyContext();

        window.Close();
    }
}