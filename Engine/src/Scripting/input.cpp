#include "Scripting/modules.hpp"
#include "Inputs/InputHandler.hpp"
#include <unordered_map>
#include "Debug/Logger.hpp"

namespace BwatEngine
{
    std::unordered_map<std::string, Keyboard> keyMap;
    std::unordered_map<std::string, Mouse> mouseMap;

#define INIT_KEYMAP()                       \
keyMap["space"] = KEY_SPACE;                \
keyMap["'"] = KEY_APOSTROPHE;               \
keyMap[","] = KEY_COMMA;                    \
keyMap["-"] = KEY_MINUS;                    \
keyMap["."] = KEY_PERIOD;                   \
keyMap["/"] = KEY_SLASH;                    \
keyMap["0"] = KEY_0;                        \
keyMap["1"] = KEY_1;                        \
keyMap["2"] = KEY_2;                        \
keyMap["3"] = KEY_3;                        \
keyMap["4"] = KEY_4;                        \
keyMap["5"] = KEY_5;                        \
keyMap["6"] = KEY_6;                        \
keyMap["7"] = KEY_7;                        \
keyMap["8"] = KEY_8;                        \
keyMap["9"] = KEY_9;                        \
keyMap[";"] = KEY_SEMICOLON;                \
keyMap["="] = KEY_EQUAL;                    \
keyMap["a"] = KEY_A;                        \
keyMap["b"] = KEY_B;                        \
keyMap["c"] = KEY_C;                        \
keyMap["d"] = KEY_D;                        \
keyMap["e"] = KEY_E;                        \
keyMap["f"] = KEY_F;                        \
keyMap["g"] = KEY_G;                        \
keyMap["h"] = KEY_H;                        \
keyMap["i"] = KEY_I;                        \
keyMap["j"] = KEY_J;                        \
keyMap["k"] = KEY_K;                        \
keyMap["l"] = KEY_L;                        \
keyMap["m"] = KEY_M;                        \
keyMap["n"] = KEY_N;                        \
keyMap["o"] = KEY_O;                        \
keyMap["p"] = KEY_P;                        \
keyMap["q"] = KEY_Q;                        \
keyMap["r"] = KEY_R;                        \
keyMap["s"] = KEY_S;                        \
keyMap["t"] = KEY_T;                        \
keyMap["u"] = KEY_U;                        \
keyMap["v"] = KEY_V;                        \
keyMap["w"] = KEY_W;                        \
keyMap["x"] = KEY_X;                        \
keyMap["y"] = KEY_Y;                        \
keyMap["z"] = KEY_Z;                        \
keyMap["["] = KEY_LEFT_BRACKET;             \
keyMap["\\"] = KEY_BACKSLASH;               \
keyMap["]"] = KEY_RIGHT_BRACKET;            \
keyMap["`"] = KEY_GRAVE_ACCENT;             \
keyMap["escape"] = KEY_ESCAPE;              \
keyMap["enter"] = KEY_ENTER;                \
keyMap["tab"] = KEY_TAB;                    \
keyMap["backspace"] = KEY_BACKSPACE;        \
keyMap["insert"] = KEY_INSERT;              \
keyMap["delete"] = KEY_DELETE;              \
keyMap["right"] = KEY_RIGHT;                \
keyMap["left"] = KEY_LEFT;                  \
keyMap["down"] = KEY_DOWN;                  \
keyMap["up"] = KEY_UP;                      \
keyMap["pageup"] = KEY_PAGE_UP;             \
keyMap["pagedown"] = KEY_PAGE_DOWN;         \
keyMap["home"] = KEY_HOME;                  \
keyMap["end"] = KEY_END;                    \
keyMap["capslock"] = KEY_CAPS_LOCK;         \
keyMap["scrolllock"] = KEY_SCROLL_LOCK;     \
keyMap["numlock"] = KEY_NUM_LOCK;           \
keyMap["printscreen"] = KEY_PRINT_SCREEN;   \
keyMap["pause"] = KEY_PAUSE;                \
keyMap["f1"] = KEY_F1;                      \
keyMap["f2"] = KEY_F2;                      \
keyMap["f3"] = KEY_F3;                      \
keyMap["f4"] = KEY_F4;                      \
keyMap["f5"] = KEY_F5;                      \
keyMap["f6"] = KEY_F6;                      \
keyMap["f7"] = KEY_F7;                      \
keyMap["f8"] = KEY_F8;                      \
keyMap["f9"] = KEY_F9;                      \
keyMap["f10"] = KEY_F10;                    \
keyMap["f11"] = KEY_F11;                    \
keyMap["f12"] = KEY_F12;                    \
keyMap["kp0"] = KEY_KP_0;                   \
keyMap["kp1"] = KEY_KP_1;                   \
keyMap["kp2"] = KEY_KP_2;                   \
keyMap["kp3"] = KEY_KP_3;                   \
keyMap["kp4"] = KEY_KP_4;                   \
keyMap["kp5"] = KEY_KP_5;                   \
keyMap["kp6"] = KEY_KP_6;                   \
keyMap["kp7"] = KEY_KP_7;                   \
keyMap["kp8"] = KEY_KP_8;                   \
keyMap["kp9"] = KEY_KP_9;                   \
keyMap["kp."] = KEY_KP_DECIMAL;             \
keyMap["kp/"] = KEY_KP_DIVIDE;              \
keyMap["kp*"] = KEY_KP_MULTIPLY;            \
keyMap["kp-"] = KEY_KP_SUBTRACT;            \
keyMap["kp+"] = KEY_KP_ADD;                 \
keyMap["kpenter"] = KEY_KP_ENTER;           \
keyMap["kp="] = KEY_KP_EQUAL;               \
keyMap["lshift"] = KEY_LEFT_SHIFT;          \
keyMap["lctrl"] = KEY_LEFT_CONTROL;         \
keyMap["lalt"] = KEY_LEFT_ALT;              \
keyMap["lsuper"] = KEY_LEFT_SUPER;          \
keyMap["rshift"] = KEY_RIGHT_SHIFT;         \
keyMap["rctrl"] = KEY_RIGHT_CONTROL;        \
keyMap["ralt"] = KEY_RIGHT_ALT;             \
keyMap["rsuper"] = KEY_RIGHT_SUPER;         \
keyMap["menu"] = KEY_MENU;

    Keyboard GetKeyFromString(std::string &key)
    {
        auto keyPair = keyMap.find(key);
        if (keyPair != keyMap.end())
        {
            return keyPair->second;
        }
        return Keyboard::KEY_UNKNOWN;
    }

#define INIT_MOUSEMAP() \
mouseMap["left"] = MOUSE_BUTTON_1;\
mouseMap["right"] = MOUSE_BUTTON_2;\
mouseMap["middle"] = MOUSE_BUTTON_3;\
mouseMap["mouse4"] = MOUSE_BUTTON_4;\
mouseMap["mouse5"] = MOUSE_BUTTON_5;\
mouseMap["mouse6"] = MOUSE_BUTTON_6;\
mouseMap["mouse7"] = MOUSE_BUTTON_7;\
mouseMap["mouse8"] = MOUSE_BUTTON_8;\


    Mouse GetMouseButtonFromString(std::string &key)
    {
        auto mousePair = mouseMap.find(key);
        if (mousePair != mouseMap.end())
        {
            return mousePair->second;
        }
        return Mouse::MOUSE_BUTTON_1;
    }

#define GENERATE_KEYBOARD_FUNC(function)                    \
bool function(std::string key)                              \
{                                                           \
    return InputHandler::function(GetKeyFromString(key));   \
}

#define GENERATE_MOUSE_FUNC(function)                    \
bool function(std::string key)                              \
{                                                           \
    return InputHandler::function(GetMouseButtonFromString(key));   \
}

    GENERATE_KEYBOARD_FUNC(GetKeyboardDown)
    GENERATE_KEYBOARD_FUNC(GetKeyboardUp)
    GENERATE_KEYBOARD_FUNC(GetKeyboard)

    GENERATE_MOUSE_FUNC(GetMouseButtonDown)
    GENERATE_MOUSE_FUNC(GetMouseButtonUp)
    GENERATE_MOUSE_FUNC(GetMouseButton)

    bool GetAnyKeyDown()
    {
        return InputHandler::GetAnyKeyDown();
    }

    Math::Vec2d GetMousePos()
    {
        return InputHandler::GetMousePos();
    }
    Math::Vec2d GetMouseDelta()
    {
        return InputHandler::GetMouseDelta();
    }
    Math::Vec2d GetScrollDelta()
    {
        return InputHandler::GetScrollDelta();
    }


    sol::table open_input(sol::this_state s)
    {
        sol::state_view lua(s);

        sol::table module = lua.create_table();

        INIT_KEYMAP();
        INIT_MOUSEMAP();

#define REGISTER_FUNC(function) module.set_function(#function, function)

        REGISTER_FUNC(GetKeyboardDown);
        REGISTER_FUNC(GetKeyboardUp);
        REGISTER_FUNC(GetKeyboard);

        REGISTER_FUNC(GetAnyKeyDown);

        REGISTER_FUNC(GetMouseButtonDown);
        REGISTER_FUNC(GetMouseButtonUp);
        REGISTER_FUNC(GetMouseButton);

        REGISTER_FUNC(GetMousePos);
        REGISTER_FUNC(GetMouseDelta);
        REGISTER_FUNC(GetScrollDelta);


#undef REGISTER_FUNC

        return module;
    }
}
#undef INIT_KEYMAP
#undef INIT_MOUSEMAP