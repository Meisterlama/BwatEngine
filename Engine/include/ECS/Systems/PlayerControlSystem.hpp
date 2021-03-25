#ifndef ENGINE_ECS_SYSTEMS_PLAYER_CONTROL_HPP
#define ENGINE_ECS_SYSTEMS_PLAYER_CONTROL_HPP

#include "Math/Common.hpp"
#include "ECS/System.hpp"
#include "Inputs/InputHandler.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"

namespace BwatEngine
{
    class PlayerControlSystem: public System
    {
        bool lockMouse = false;
        Math::Vec3f rotation{};
    public:
        void Init()
        {};

        void Update(float dt, GLFWwindow *win)
        {
            if (InputHandler::GetKeyboardDown(KEY_F1)) {
                lockMouse = !lockMouse;
                glfwSetInputMode(win, GLFW_CURSOR, (lockMouse) ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
            }
            if (lockMouse) {
                for (auto &entityId : entities) {
                    auto coordinator = Coordinator::GetInstance();
                    auto &transform = coordinator->GetComponent<TransformComponent>(entityId).transform;

                    Math::Vec2f mouseDelta = InputHandler::GetMouseDelta();
                    float sensitivity_mouse = 0.1f;
                    mouseDelta *= sensitivity_mouse * dt;

//                    if (Math::Quatf(rotation) != transform.rotation)
//                        rotation = transform.rotation.GetEulerAngles();

                    rotation.Y += mouseDelta.X;
                    rotation.X += mouseDelta.Y;


                    if (rotation.X > (Math::PI/2 - 0.001))
                        rotation.X = (Math::PI/2 - 0.001);
                    else if (rotation.X < -(Math::PI/2 - 0.001))
                        rotation.X = -(Math::PI/2 - 0.001) ;

                    if(InputHandler::GetKeyboard(KEY_Q))
                    {
                        rotation.Z -= 2 * dt;
                    }
                    if(InputHandler::GetKeyboard(KEY_E))
                    {
                        rotation.Z += 2 * dt;
                    }

                    transform.rotation = {rotation};

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

                    Math::Vec3f forwardVec = transform.rotation.Rotate({0, 0, 1}).Normalize();
                    Math::Vec3f rightVec = transform.rotation.Rotate({1, 0, 0}).Normalize();

                    Math::Vec3f translation = forwardVec * ForwardVelocity + rightVec * StrafeVelocity;

                    transform.position += translation;
                }
            }
        }
    };
}

#endif //ENGINE_ECS_SYSTEMS_PLAYER_CONTROL_HPP