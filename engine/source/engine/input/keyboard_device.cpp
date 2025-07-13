#include <silk/engine/input/keyboard_device.h>

#include <silk/core/assert.h>
#include <silk/engine/window/application_window.h>

namespace silk
{

    KeyboardDevice::KeyboardDevice()
        : InputDevice{}
        , m_OnKeyInputSlot{}
    {
        m_DeviceId.data.deviceType = InputDeviceType::Keyboard;
    }

    void KeyboardDevice::Init(ApplicationWindow& window)
    {
        m_OnKeyInputSlot.SetBoundFunction([this](InputId inputId, bool isPressed) { OnKeyInput(inputId, isPressed); });
        window.GetKeyboardInputSignal().Connect(m_OnKeyInputSlot);
    }

    void KeyboardDevice::Shutdown(ApplicationWindow& window)
    {
        window.GetKeyboardInputSignal().Disconnect(m_OnKeyInputSlot);
    }

    void KeyboardDevice::SwapStateBuffers()
    {
        const auto& prevState{ m_InputStates[m_CurrentInputStateIndex] };
        m_CurrentInputStateIndex = (m_CurrentInputStateIndex + 1) % INPUT_STATE_BUFFER_COUNT;
        m_InputStates[m_CurrentInputStateIndex] = prevState;
    }

    float KeyboardDevice::GetAnalogState(InputId) const
    {
        SILK_ASSERT(false, "Keyboards do not have analog states.");
        return 0.0f;
    }

    bool KeyboardDevice::GetButtonState(InputId inputId) const
    {
        return m_InputStates[m_CurrentInputStateIndex].test(static_cast<size_t>(inputId));
    }

    bool KeyboardDevice::GetButtonPreviousState(InputId inputId) const
    {
        return m_InputStates[(m_CurrentInputStateIndex + 1) % INPUT_STATE_BUFFER_COUNT].test(static_cast<size_t>(inputId));
    }

    void KeyboardDevice::OnKeyInput(InputId inputId, bool isPressed)
    {
        m_InputStates[m_CurrentInputStateIndex].set((size_t)inputId, isPressed);
    }

}
