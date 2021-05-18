#include "ECS/Systems/PlayerControlSystem.hpp"
#include "Inputs/InputHandler.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "Math/Quaternion.hpp"
#include "AL/al.h"
#include "Time.hpp"
namespace BwatEngine
{
    void PlayerControlSystem::Update()
    {
        if (InputHandler::GetKeyboardDown(KEY_F1)) {
            lockMouse = !lockMouse;
            InputHandler::SetMouseStatus((lockMouse) ? Disabled : Normal);
            for (auto& entityId: entities)
            {
                rotation = Coordinator::GetInstance().GetComponent<TransformComponent>(entityId).rotation.GetEulerAngles();
            }
        }
        if (lockMouse) {
            for (auto &entityId : entities) {
                auto& coordinator = Coordinator::GetInstance();
                auto &transform = coordinator.GetComponent<TransformComponent>(entityId);

                Math::Vec2f mouseDelta = InputHandler::GetMouseDelta();
                float sensitivity_mouse = -0.1f;
                mouseDelta *= sensitivity_mouse * Time::deltaTime;

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
                    rotation.Z -= 2 * Time::deltaTime;
                }
                if(InputHandler::GetKeyboard(KEY_E))
                {
                    rotation.Z += 2 * Time::deltaTime;
                }

                transform.rotation = {rotation};

                float Speed = 25.f;
                float FrameSpeed = Speed * Time::deltaTime;


                if (InputHandler::GetKeyboard(KEY_LEFT_SHIFT))
                    FrameSpeed *= 5.f;


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
                    transform.position.Y += Speed * Time::deltaTime;

                if (InputHandler::GetKeyboard(KEY_LEFT_CONTROL))
                    transform.position.Y -= Speed * Time::deltaTime;

                Math::Vec3f forwardVec = transform.rotation.Rotate({0, 0, 1}).Normalize();
                Math::Vec3f rightVec = transform.rotation.Rotate({1, 0, 0}).Normalize();
                Math::Vec3f upVec = transform.rotation.Rotate({0, 1,0}).Normalize();

                Math::Vec3f translation = forwardVec * ForwardVelocity + rightVec * StrafeVelocity;

                transform.position += translation;

                float orientation[6] = {
                        -forwardVec.X,
                        -forwardVec.Y,
                        -forwardVec.Z,
                        upVec.X,
                        upVec.Y,
                        upVec.Z,
                };

                alListenerfv(AL_POSITION, transform.position.values);
                alListenerfv(AL_ORIENTATION, orientation);

//                    float vector[3];

//                    alGetListener3f(AL_POSITION, &vector[0], &vector[1], &vector[2]);

//                    LogDebug("%f, %f, %f", vector[0], vector[1], vector[2]);
            }
        }
    }
}