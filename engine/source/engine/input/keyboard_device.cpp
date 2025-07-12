#include <silk/engine/input/keyboard_device.h>

#include <glfw/glfw3.h>

#include <silk/engine/window/application_window.h>

namespace silk
{

    void KeyboardDevice::Init(ApplicationWindow& window)
    {
        m_OnKeyInputSlot.SetBoundFunction([this](InputId inputId, bool isPressed) { OnkeyInput(inputId, isPressed); });
        window.GetKeyboardInputSignal().Connect(m_OnKeyInputSlot);
    }

    void KeyboardDevice::Shutdown(ApplicationWindow& window)
    {
        window.GetKeyboardInputSignal().Disconnect(m_OnKeyInputSlot);
    }

    void KeyboardDevice::OnkeyInput(InputId inputId, bool isPressed)
    {
        m_ButtonInputStateChanged.Raise(inputId, isPressed);
    }
}