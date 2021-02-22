#include "Inputs/InputHandler.hpp"
#include "Debug/Logger.hpp"
#include <GLFW/glfw3.h>
namespace BwatEngine
{
    InputHandler* InputHandler::inputHandler= nullptr;;

    void InputHandler::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        auto* handler = GetInstance();
        bool oldPress = handler->keyboard[(Keyboard)key].pressed;
        handler->keyboard[(Keyboard)key].pressed = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        handler->keyboard[(Keyboard)key].down = !oldPress && (action == GLFW_PRESS);
        handler->keyboard[(Keyboard)key].up = oldPress && (action == GLFW_RELEASE);


        LogTrace("Mod: %i; Key: %s(%i) %s", mods, glfwGetKeyName(key, 0), key, (action == 0) ? "released" : ((action == 1) ? "pressed" : "repeated"));
    }
    void InputHandler::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
    {
        LogTrace("MouseButton : (%i) %s", button, (action == GLFW_PRESS)? "pressed." : "released");
    }
    void InputHandler::Initialize(GLFWwindow *_window)
    {
        glfwSetKeyCallback(_window, InputHandler::KeyCallback);
        glfwSetMouseButtonCallback(_window, InputHandler::MouseButtonCallback);

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
        InputHandler* handler = GetInstance();
        for (auto keyState : (handler->keyboard))
        {
            handler->keyboard[keyState.first].down = false;
            handler->keyboard[keyState.first].up = false;
        }

        for (auto buttonState : handler->mouse)
        {
            buttonState.second.down = false;
            buttonState.second.up = false;
        }
    }

    bool InputHandler::GetKeyboardDown(Keyboard key) {return GetInstance()->keyboard[key].down;}
    bool InputHandler::GetKeyboardUp(Keyboard key) {return GetInstance()->keyboard[key].up;}
    bool InputHandler::GetKeyboard(Keyboard key) {return GetInstance()->keyboard[key].pressed;}
    bool InputHandler::GetMouseButtonDown(Mouse button) {return GetInstance()->mouse[button].down;}
    bool InputHandler::GetMouseButtonUp(Mouse button) {return GetInstance()->mouse[button].up;}
    bool InputHandler::GetMouseButton(Mouse button) {return GetInstance()->mouse[button].pressed;}
}

