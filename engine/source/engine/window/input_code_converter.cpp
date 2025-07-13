#include "input_code_converter.h"

#include <unordered_map>

#include <glfw/glfw3.h>

namespace silk::input
{
    InputId ConvertedGlfwKeyToInputId(int glfwKey)
    {
        static std::unordered_map<int, KeyboardInputId> keyToInputMap
        {
            { GLFW_KEY_SPACE, KeyboardInputId::KeySpace },
            { GLFW_KEY_0, KeyboardInputId::Key0 },
            { GLFW_KEY_1, KeyboardInputId::Key1 },
            { GLFW_KEY_2, KeyboardInputId::Key2 },
            { GLFW_KEY_3, KeyboardInputId::Key3 },
            { GLFW_KEY_4, KeyboardInputId::Key4 },
            { GLFW_KEY_5, KeyboardInputId::Key5 },
            { GLFW_KEY_6, KeyboardInputId::Key6 },
            { GLFW_KEY_7, KeyboardInputId::Key7 },
            { GLFW_KEY_8, KeyboardInputId::Key8 },
            { GLFW_KEY_9, KeyboardInputId::Key9 },
            { GLFW_KEY_A, KeyboardInputId::KeyA },
            { GLFW_KEY_B, KeyboardInputId::KeyB },
            { GLFW_KEY_C, KeyboardInputId::KeyC },
            { GLFW_KEY_D, KeyboardInputId::KeyD },
            { GLFW_KEY_E, KeyboardInputId::KeyE },
            { GLFW_KEY_F, KeyboardInputId::KeyF },
            { GLFW_KEY_G, KeyboardInputId::KeyG },
            { GLFW_KEY_H, KeyboardInputId::KeyH },
            { GLFW_KEY_I, KeyboardInputId::KeyI },
            { GLFW_KEY_J, KeyboardInputId::KeyJ },
            { GLFW_KEY_K, KeyboardInputId::KeyK },
            { GLFW_KEY_L, KeyboardInputId::KeyL },
            { GLFW_KEY_M, KeyboardInputId::KeyM },
            { GLFW_KEY_N, KeyboardInputId::KeyN },
            { GLFW_KEY_O, KeyboardInputId::KeyO },
            { GLFW_KEY_P, KeyboardInputId::KeyP },
            { GLFW_KEY_Q, KeyboardInputId::KeyQ },
            { GLFW_KEY_R, KeyboardInputId::KeyR },
            { GLFW_KEY_S, KeyboardInputId::KeyS },
            { GLFW_KEY_T, KeyboardInputId::KeyT },
            { GLFW_KEY_U, KeyboardInputId::KeyU },
            { GLFW_KEY_V, KeyboardInputId::KeyV },
            { GLFW_KEY_W, KeyboardInputId::KeyW },
            { GLFW_KEY_X, KeyboardInputId::KeyX },
            { GLFW_KEY_Y, KeyboardInputId::KeyY },
            { GLFW_KEY_Z, KeyboardInputId::KeyZ },
            { GLFW_KEY_ESCAPE, KeyboardInputId::KeyEscape },
            { GLFW_KEY_ENTER, KeyboardInputId::KeyEnter },
            { GLFW_KEY_TAB, KeyboardInputId::KeyTab },
            { GLFW_KEY_BACKSPACE, KeyboardInputId::KeyBackspace },
            { GLFW_KEY_INSERT, KeyboardInputId::KeyInsert },
            { GLFW_KEY_DELETE, KeyboardInputId::KeyDelete },
            { GLFW_KEY_RIGHT, KeyboardInputId::KeyRight },
            { GLFW_KEY_LEFT, KeyboardInputId::KeyLeft },
            { GLFW_KEY_DOWN, KeyboardInputId::KeyDown },
            { GLFW_KEY_UP, KeyboardInputId::KeyUp },
            { GLFW_KEY_F1, KeyboardInputId::KeyF1 },
            { GLFW_KEY_F2, KeyboardInputId::KeyF2 },
            { GLFW_KEY_F3, KeyboardInputId::KeyF3 },
            { GLFW_KEY_F4, KeyboardInputId::KeyF4 },
            { GLFW_KEY_F5, KeyboardInputId::KeyF5 },
            { GLFW_KEY_F6, KeyboardInputId::KeyF6 },
            { GLFW_KEY_F7, KeyboardInputId::KeyF7 },
            { GLFW_KEY_F8, KeyboardInputId::KeyF8 },
            { GLFW_KEY_F9, KeyboardInputId::KeyF9 },
            { GLFW_KEY_F10, KeyboardInputId::KeyF10 },
            { GLFW_KEY_F11, KeyboardInputId::KeyF11 },
            { GLFW_KEY_F12, KeyboardInputId::KeyF12 },
            { GLFW_KEY_LEFT_SHIFT, KeyboardInputId::KeyLShift },
            { GLFW_KEY_LEFT_CONTROL, KeyboardInputId::KeyLControl },
            { GLFW_KEY_LEFT_ALT, KeyboardInputId::KeyLAlt },
            { GLFW_KEY_RIGHT_SHIFT, KeyboardInputId::KeyRShift },
            { GLFW_KEY_RIGHT_CONTROL, KeyboardInputId::KeyRControl },
            { GLFW_KEY_RIGHT_ALT, KeyboardInputId::KeyRAlt },
            { GLFW_KEY_MENU, KeyboardInputId::KeyMenu },
        };

        KeyboardInputId inputId{ KeyboardInputId::Undefined };
        auto foundIt{ keyToInputMap.find(glfwKey) };
        if (foundIt != keyToInputMap.end())
        {
            inputId = foundIt->second;
        }
        return (InputId)inputId;
    }
}
