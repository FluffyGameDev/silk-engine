#include "input_code_converter.h"

#include <unordered_map>

#include <glfw/glfw3.h>

namespace silk::input
{
    InputId ConvertedGlfwKeyToInputId(int glfwKey)
    {
        static std::unordered_map<int, InputId> keyToInputMap
        {
            { GLFW_KEY_SPACE, InputId::KeySpace },
            { GLFW_KEY_0, InputId::Key0 },
            { GLFW_KEY_1, InputId::Key1 },
            { GLFW_KEY_2, InputId::Key2 },
            { GLFW_KEY_3, InputId::Key3 },
            { GLFW_KEY_4, InputId::Key4 },
            { GLFW_KEY_5, InputId::Key5 },
            { GLFW_KEY_6, InputId::Key6 },
            { GLFW_KEY_7, InputId::Key7 },
            { GLFW_KEY_8, InputId::Key8 },
            { GLFW_KEY_9, InputId::Key9 },
            { GLFW_KEY_A, InputId::KeyA },
            { GLFW_KEY_B, InputId::KeyB },
            { GLFW_KEY_C, InputId::KeyC },
            { GLFW_KEY_D, InputId::KeyD },
            { GLFW_KEY_E, InputId::KeyE },
            { GLFW_KEY_F, InputId::KeyF },
            { GLFW_KEY_G, InputId::KeyG },
            { GLFW_KEY_H, InputId::KeyH },
            { GLFW_KEY_I, InputId::KeyI },
            { GLFW_KEY_J, InputId::KeyJ },
            { GLFW_KEY_K, InputId::KeyK },
            { GLFW_KEY_L, InputId::KeyL },
            { GLFW_KEY_M, InputId::KeyM },
            { GLFW_KEY_N, InputId::KeyN },
            { GLFW_KEY_O, InputId::KeyO },
            { GLFW_KEY_P, InputId::KeyP },
            { GLFW_KEY_Q, InputId::KeyQ },
            { GLFW_KEY_R, InputId::KeyR },
            { GLFW_KEY_S, InputId::KeyS },
            { GLFW_KEY_T, InputId::KeyT },
            { GLFW_KEY_U, InputId::KeyU },
            { GLFW_KEY_V, InputId::KeyV },
            { GLFW_KEY_W, InputId::KeyW },
            { GLFW_KEY_X, InputId::KeyX },
            { GLFW_KEY_Y, InputId::KeyY },
            { GLFW_KEY_Z, InputId::KeyZ },
            { GLFW_KEY_ESCAPE, InputId::KeyEscape },
            { GLFW_KEY_ENTER, InputId::KeyEnter },
            { GLFW_KEY_TAB, InputId::KeyTab },
            { GLFW_KEY_BACKSPACE, InputId::KeyBackspace },
            { GLFW_KEY_INSERT, InputId::KeyInsert },
            { GLFW_KEY_DELETE, InputId::KeyDelete },
            { GLFW_KEY_RIGHT, InputId::KeyRight },
            { GLFW_KEY_LEFT, InputId::KeyLeft },
            { GLFW_KEY_DOWN, InputId::KeyDown },
            { GLFW_KEY_UP, InputId::KeyUp },
            { GLFW_KEY_F1, InputId::KeyF1 },
            { GLFW_KEY_F2, InputId::KeyF2 },
            { GLFW_KEY_F3, InputId::KeyF3 },
            { GLFW_KEY_F4, InputId::KeyF4 },
            { GLFW_KEY_F5, InputId::KeyF5 },
            { GLFW_KEY_F6, InputId::KeyF6 },
            { GLFW_KEY_F7, InputId::KeyF7 },
            { GLFW_KEY_F8, InputId::KeyF8 },
            { GLFW_KEY_F9, InputId::KeyF9 },
            { GLFW_KEY_F10, InputId::KeyF10 },
            { GLFW_KEY_F11, InputId::KeyF11 },
            { GLFW_KEY_F12, InputId::KeyF12 },
            { GLFW_KEY_LEFT_SHIFT, InputId::KeyLShift },
            { GLFW_KEY_LEFT_CONTROL, InputId::KeyLControl },
            { GLFW_KEY_LEFT_ALT, InputId::KeyLAlt },
            { GLFW_KEY_RIGHT_SHIFT, InputId::KeyRShift },
            { GLFW_KEY_RIGHT_CONTROL, InputId::KeyRControl },
            { GLFW_KEY_RIGHT_ALT, InputId::KeyRAlt },
            { GLFW_KEY_MENU, InputId::KeyMenu },
        };

        InputId inputId{ InputId::Undefined };
        auto foundIt{ keyToInputMap.find(glfwKey) };
        if (foundIt != keyToInputMap.end())
        {
            inputId = foundIt->second;
        }
        return inputId;
    }
}
