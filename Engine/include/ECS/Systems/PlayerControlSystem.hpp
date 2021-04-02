#ifndef ENGINE_ECS_SYSTEMS_PLAYER_CONTROL_HPP
#define ENGINE_ECS_SYSTEMS_PLAYER_CONTROL_HPP

#include "ECS/System.hpp"
#include "Inputs/InputHandler.hpp"

namespace BwatEngine
{
    class PlayerControlSystem: public System
    {
        bool lockMouse = false;
    public:
        void Init()
        {};

        void Update(float dt, Window &win)
        {
            if (InputHandler::GetKeyboardDown(KEY_F1)) {
                lockMouse = !lockMouse;
                glfwSetInputMode(win.window, GLFW_CURSOR, (lockMouse) ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
            }
            if (lockMouse) {
                for (auto &entityId : entities) {
                    auto coordinator = Coordinator::GetInstance();
                    auto &transform = coordinator->GetComponent<TransformComponent>(entityId).transform;

                    Math::Vec2f mouseDelta = InputHandler::GetMouseDelta();
                    float sensitivity_mouse = 0.1f;
                    mouseDelta *= sensitivity_mouse * dt;

                    transform.rotation.Y -= mouseDelta.X;
                    transform.rotation.X -= mouseDelta.Y;

                    if (transform.rotation.X >= Math::PI / 2)
                        transform.rotation.X = Math::PI / 2;

                    else if (transform.rotation.X <= -Math::PI / 2)
                        transform.rotation.X = -Math::PI / 2;

                    float Speed = 4.f;
                    float FrameSpeed = Speed * dt;


                    if (InputHandler::GetKeyboard(KEY_LEFT_SHIFT))
                        FrameSpeed *= 3.f;


                    float ForwardVelocity = 0.f;
                    if (InputHandler::GetKeyboard(KEY_W))
                        ForwardVelocity = -FrameSpeed;
                    if (InputHandler::GetKeyboard(KEY_S))
                        ForwardVelocity = FrameSpeed;


                    float StrafeVelocity = 0.f;
                    if (InputHandler::GetKeyboard(KEY_A))
                        StrafeVelocity = -FrameSpeed;
                    if (InputHandler::GetKeyboard(KEY_D))
                        StrafeVelocity = FrameSpeed;

                    if (InputHandler::GetKeyboard(KEY_SPACE))
                        transform.position.Y += Speed * dt;

                    if (InputHandler::GetKeyboard(KEY_LEFT_CONTROL))
                        transform.position.Y -= Speed * dt;

                    transform.position.Z += cos(-transform.rotation.Y) * cos(transform.rotation.X) * ForwardVelocity;
                    transform.position.X += sin(transform.rotation.Y) * cos(-transform.rotation.X) * ForwardVelocity;
                    transform.position.Y -= sin(transform.rotation.X) * ForwardVelocity;

                    transform.position.Z += sin(-transform.rotation.Y) * StrafeVelocity;
                    transform.position.X += cos(-transform.rotation.Y) * StrafeVelocity;
                }
            }
        }
    };
}

#endif //ENGINE_ECS_SYSTEMS_PLAYER_CONTROL_HPP