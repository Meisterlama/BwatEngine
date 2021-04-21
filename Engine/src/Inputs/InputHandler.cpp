#include "Inputs/InputHandler.hpp"
#include "Debug/Logger.hpp"

#include "imgui_impl_glfw.h"

namespace BwatEngine
{
    InputHandler* InputHandler::inputHandler= nullptr;;

    void InputHandler::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        inputHandler->keyboard[(Keyboard)key].pressed = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        inputHandler->keyboard[(Keyboard)key].down = (action == GLFW_PRESS);
        inputHandler->keyboard[(Keyboard)key].up = (action == GLFW_RELEASE);

        ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
//        LogTrace("Mod: %i; Key: %s(%i) %s",
//                 mods, glfwGetKeyName(key, 0), key, (action == 0) ? "released" : ((action == 1) ? "pressed" : "repeated"));
    }
    void InputHandler::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
    {
        inputHandler->mouse[(Mouse)button].pressed = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        inputHandler->mouse[(Mouse)button].down = (action == GLFW_PRESS);
        inputHandler->mouse[(Mouse)button].up = (action == GLFW_RELEASE);

        ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
//        LogTrace("Mouse button %i(mod %i) %s",
//                 button, mods, (action == 0) ? "released" : ((action == 1) ? "pressed" : "repeated"));
    }

    void InputHandler::MouseMovementCallback(GLFWwindow* window, double xpos, double ypos)
    {
        inputHandler->mousePos = {xpos, ypos};

        BwatEngine::Math::Vec2d mouseDelta = inputHandler->mousePos - inputHandler->mouseOldPos;

//        LogDebug("\nOldPos X:%f;Y:%f,\nNewPos X:%f;Y:%f,\nDelta X:%f;Y:%f",
//                 inputHandler->mouseOldPos.X, inputHandler->mouseOldPos.Y,
//                 xpos, ypos,
//                 mouseDelta.X, mouseDelta.Y);
    }

    void InputHandler::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        inputHandler->scrollDelta = {xoffset, yoffset};
        ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
//        LogDebug("\nScroll Delta: X:%f;Y:%f",
//                 xoffset, yoffset);
    }

    void InputHandler::Initialize(GLFWwindow *_window)
    {
        glfwSetKeyCallback(_window, InputHandler::KeyCallback);
        glfwSetMouseButtonCallback(_window, InputHandler::MouseButtonCallback);
        glfwSetCursorPosCallback(_window, InputHandler::MouseMovementCallback);
        glfwSetScrollCallback(_window, InputHandler::ScrollCallback);
        glfwSetCharCallback(_window, ImGui_ImplGlfw_CharCallback);

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
        glfwPollEvents();
        inputHandler->mouseDelta = inputHandler->mousePos - inputHandler->mouseOldPos;
        inputHandler->mouseOldPos = inputHandler->mousePos;
    }

    bool InputHandler::GetKeyboardDown(Keyboard key) {return inputHandler->keyboard[key].down;}
    bool InputHandler::GetKeyboardUp(Keyboard key) {return inputHandler->keyboard[key].up;}
    bool InputHandler::GetKeyboard(Keyboard key) {return inputHandler->keyboard[key].pressed;}
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
//        if (status == Disabled)
//        {
//            ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
//        }
//        else
//        {
//            ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
//        }
    }

    MouseStatus InputHandler::GetMouseStatus()
    {
        return inputHandler->mouseStatus;
    }
}

