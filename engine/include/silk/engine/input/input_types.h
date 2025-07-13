#pragma once

#include <silk/core/types.h>

namespace silk
{

    enum class InputDeviceType : u8
    {
        Keyboard,
        Mouse,
        Gamepad,
        Other,
    };

    union InputDeviceId
    {
        struct
        {
            InputDeviceType deviceType;
            u8 deviceNumber;
        } data;
        u16 deviceId;
    };

    using InputId = u32;

    enum class KeyboardInputId : u32
    {
        KeySpace,

        Key0,
        Key1,
        Key2,
        Key3,
        Key4,
        Key5,
        Key6,
        Key7,
        Key8,
        Key9,

        KeyA,
        KeyB,
        KeyC,
        KeyD,
        KeyE,
        KeyF,
        KeyG,
        KeyH,
        KeyI,
        KeyJ,
        KeyK,
        KeyL,
        KeyM,
        KeyN,
        KeyO,
        KeyP,
        KeyQ,
        KeyR,
        KeyS,
        KeyT,
        KeyU,
        KeyV,
        KeyW,
        KeyX,
        KeyY,
        KeyZ,

        KeyEscape,
        KeyEnter,
        KeyTab,
        KeyBackspace,
        KeyInsert,
        KeyDelete,

        KeyRight,
        KeyLeft,
        KeyDown,
        KeyUp,

        KeyF1,
        KeyF2,
        KeyF3,
        KeyF4,
        KeyF5,
        KeyF6,
        KeyF7,
        KeyF8,
        KeyF9,
        KeyF10,
        KeyF11,
        KeyF12,

        KeyLShift,
        KeyLControl,
        KeyLAlt,
        KeyRShift,
        KeyRControl,
        KeyRAlt,
        KeyMenu,

        Count = KeyMenu,
        Undefined = static_cast<u32>(-1),
    };

    enum class MouseInputId : u32
    {
        LeftButton,
        MiddleButton,
        RightButton,

        CursorX,
        CursorY,

        Count = CursorY,
        Undefined = static_cast<u32>(-1),
    };

}
