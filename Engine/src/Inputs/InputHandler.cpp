#include <algorithm>
#include "Inputs/InputHandler.hpp"

#if defined(BWATEDITOR)
#include "imgui_impl_glfw.h"
#endif

namespace BwatEngine
{
    InputHandler* InputHandler::inputHandler= nullptr;;

    void InputHandler::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        inputHandler->keyboard[static_cast<Keyboard>(key)].pressed = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        inputHandler->keyboard[static_cast<Keyboard>(key)].down = (action == GLFW_PRESS);
        inputHandler->keyboard[static_cast<Keyboard>(key)].up = (action == GLFW_RELEASE);

        if ((action == GLFW_PRESS) || (action == GLFW_REPEAT))
            inputHandler->lastPressed = static_cast<Keyboard>(key);

#if defined(BWATEDITOR)
        ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
#endif
//        LogTrace("Mod: %i; Key: %s(%i) %s",
//                 mods, glfwGetKeyName(key, 0), key, (action == 0) ? "released" : ((action == 1) ? "pressed" : "repeated"));
    }
    void InputHandler::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
    {
        inputHandler->mouse[static_cast<Mouse>(button)].pressed = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        inputHandler->mouse[static_cast<Mouse>(button)].down = (action == GLFW_PRESS);
        inputHandler->mouse[static_cast<Mouse>(button)].up = (action == GLFW_RELEASE);
#if defined(BWATEDITOR)
        ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
#endif
//        LogTrace("Mouse button %i(mod %i) %s",
//                 button, mods, (action == 0) ? "released" : ((action == 1) ? "pressed" : "repeated"));
    }

    void InputHandler::MouseMovementCallback(GLFWwindow* window, double xpos, double ypos)
    {
        inputHandler->mousePos = {xpos, ypos};

//        LogDebug("\nOldPos X:%f;Y:%f,\nNewPos X:%f;Y:%f,\nDelta X:%f;Y:%f",
//                 inputHandler->mouseOldPos.X, inputHandler->mouseOldPos.Y,
//                 xpos, ypos,
//                 mouseDelta.X, mouseDelta.Y);
    }

    void InputHandler::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        inputHandler->scrollDelta = {xoffset, yoffset};
#if defined(BWATEDITOR)
        ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
#endif
//        LogDebug("\nScroll Delta: X:%f;Y:%f",
//                 xoffset, yoffset);
    }

    void InputHandler::Initialize(GLFWwindow *_window)
    {
        glfwSetKeyCallback(_window, InputHandler::KeyCallback);
        glfwSetMouseButtonCallback(_window, InputHandler::MouseButtonCallback);
        glfwSetCursorPosCallback(_window, InputHandler::MouseMovementCallback);
        glfwSetScrollCallback(_window, InputHandler::ScrollCallback);
#if defined(BWATEDITOR)
        glfwSetCharCallback(_window, ImGui_ImplGlfw_CharCallback);
#endif

        GetInstance()->window = _window;
    }

    InputHandler *InputHandler::GetInstance()
    {
        if (inputHandler == nullptr)
            inputHandler = new InputHandler;
        return inputHandler;
    }

    void InputHandler::Update()
    {
        for (auto keyState : (inputHandler->keyboard))
        {
            inputHandler->keyboard[keyState.first].down = false;
            inputHandler->keyboard[keyState.first].up = false;
        }

        for (auto buttonState : (inputHandler->mouse))
        {
            inputHandler->mouse[buttonState.first].down = false;
            inputHandler->mouse[buttonState.first].up = false;
        }
        inputHandler->scrollDelta = {0.0};

        glfwPollEvents();
        if (inputHandler->ignoreNextDelta)
        {
            inputHandler->mouseDelta = {0,0};
            inputHandler->ignoreNextDelta = false;
        }
        else
        {
            inputHandler->mouseDelta = inputHandler->mousePos - inputHandler->mouseOldPos;
        }
        inputHandler->mouseOldPos = inputHandler->mousePos;
    }

    bool InputHandler::GetKeyboardDown(Keyboard key) {return inputHandler->keyboard[key].down;}
    bool InputHandler::GetKeyboardUp(Keyboard key) {return inputHandler->keyboard[key].up;}
    bool InputHandler::GetKeyboard(Keyboard key) {return inputHandler->keyboard[key].pressed;}
    bool InputHandler::GetAnyKeyDown()
    {
        return std::any_of(inputHandler->keyboard.cbegin(), inputHandler->keyboard.cend(),
                           [](std::pair<Keyboard, InputState> keystate)
                           {
                                return keystate.second.down;
                           }
        );
    }

    Keyboard InputHandler::GetLastKeyPressed() {return inputHandler->lastPressed;};
    bool InputHandler::GetMouseButtonDown(Mouse button) {return inputHandler->mouse[button].down;}
    bool InputHandler::GetMouseButtonUp(Mouse button) {return inputHandler->mouse[button].up;}
    bool InputHandler::GetMouseButton(Mouse button) {return inputHandler->mouse[button].pressed;}
    BwatEngine::Math::Vec2d InputHandler::GetMousePos() {return inputHandler->mousePos;}
    BwatEngine::Math::Vec2d InputHandler::GetMouseDelta() {return inputHandler->mouseDelta;}
    BwatEngine::Math::Vec2d InputHandler::GetScrollDelta() {return inputHandler->scrollDelta;}

    void InputHandler::SetMouseStatus(MouseStatus status)
    {
        auto* window = GetInstance()->window;
        Math::Vec2d newMousePos = {0};
        glfwGetCursorPos(window, &newMousePos.X, &newMousePos.Y);

        GetInstance()->mouseOldPos = newMousePos;
        GetInstance()->mousePos = newMousePos;
        GetInstance()->mouseDelta = {0};

        inputHandler->mouseStatus = status;
        glfwSetInputMode(window, GLFW_CURSOR, status);
        if (status == Disabled)
        {
            inputHandler->ignoreNextDelta = true;
        }

#ifdef BWATEDITOR
        if (status == Disabled)
        {
            ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
        }
        else
        {
            ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
        }
#endif
    }

    MouseStatus InputHandler::GetMouseStatus()
    {
        return inputHandler->mouseStatus;
    }
}

