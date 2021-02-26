#ifndef ENGINE_INPUTS_INPUT_HANDLER_HPP
#define ENGINE_INPUTS_INPUT_HANDLER_HPP

#include <map>
#include "InputEnums.hpp"
#include "Math/Vector/Vectors.hpp"
namespace BwatEngine
{
    struct InputState
    {
        bool pressed = false;
        bool down = false;
        bool up = false;
    };
    class InputHandler
    {
    private:
        std::map<Keyboard, InputState> keyboard{};
        std::map<Mouse, InputState> mouse{};

        BwatEngine::Math::Vec2d mouseDelta{};
        BwatEngine::Math::Vec2d mousePos{};
        BwatEngine::Math::Vec2d mouseOldPos{};

        BwatEngine::Math::Vec2d scrollDelta{};

        InputHandler() = default;
        ~InputHandler() { if (inputHandler) delete inputHandler;}

        InputHandler(InputHandler& other) = delete;
        void operator=(const InputHandler&) = delete;


        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void MouseMovementCallback(GLFWwindow* window, double xpos, double ypos);
        static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);


    protected:
        static InputHandler* inputHandler;
        GLFWwindow* window;

    public:
        static InputHandler* GetInstance();
        static void Initialize(GLFWwindow* window);
        static void Update();
        static bool GetKeyboardDown(Keyboard key);
        static bool GetKeyboardUp(Keyboard key);
        static bool GetKeyboard(Keyboard key);
        static bool GetMouseButtonDown(Mouse button);
        static bool GetMouseButtonUp(Mouse button);
        static bool GetMouseButton(Mouse button);
        static BwatEngine::Math::Vec2d GetMousePos();
        static BwatEngine::Math::Vec2d GetMouseDelta();
        static BwatEngine::Math::Vec2d GetScrollDelta();
    };
}

#endif //ENGINE_INPUTS_INPUT_HANDLER_HPP