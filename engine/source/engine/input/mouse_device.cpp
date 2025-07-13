#include <silk/engine/input/mouse_device.h>

#include <silk/engine/window/application_window.h>

namespace silk
{

    MouseDevice::MouseDevice()
        : InputDevice{}
        , m_OnMouseInputSlot{}
        , m_OnCursorPositionSlot{}
    {
        m_DeviceId.data.deviceType = InputDeviceType::Mouse;
    }

    void MouseDevice::Init(ApplicationWindow& window)
    {
        m_OnMouseInputSlot.SetBoundFunction([this](InputId inputId, bool isPressed) { OnMouseInput(inputId, isPressed); });
        window.GetMouseInputSignal().Connect(m_OnMouseInputSlot);

        m_OnCursorPositionSlot.SetBoundFunction([this](float x, float y) { OnOnCursorPosition(x, y); });
        window.GetCursorPositionSignal().Connect(m_OnCursorPositionSlot);

        m_AnalogState[(InputId)MouseInputId::CursorX] = 0.0f;
        m_AnalogState[(InputId)MouseInputId::CursorY] = 0.0f;
    }

    void MouseDevice::Shutdown(ApplicationWindow& window)
    {
        window.GetCursorPositionSignal().Disconnect(m_OnCursorPositionSlot);
        window.GetMouseInputSignal().Disconnect(m_OnMouseInputSlot);
    }

    void MouseDevice::SwapStateBuffers()
    {
        const auto& prevState{ m_InputStates[m_CurrentInputStateIndex] };
        m_CurrentInputStateIndex = (m_CurrentInputStateIndex + 1) % INPUT_STATE_BUFFER_COUNT;
        m_InputStates[m_CurrentInputStateIndex] = prevState;
    }

    float MouseDevice::GetAnalogState(InputId inputId) const
    {
        return m_AnalogState.at(inputId);
    }

    bool MouseDevice::GetButtonState(InputId inputId) const
    {
        return m_InputStates[m_CurrentInputStateIndex].test(static_cast<size_t>(inputId));
    }

    bool MouseDevice::GetButtonPreviousState(InputId inputId) const
    {
        return m_InputStates[(m_CurrentInputStateIndex + 1) % INPUT_STATE_BUFFER_COUNT].test(static_cast<size_t>(inputId));
    }

    void MouseDevice::OnMouseInput(InputId inputId, bool isPressed)
    {
        m_InputStates[m_CurrentInputStateIndex].set((size_t)inputId, isPressed);
    }

    void MouseDevice::OnOnCursorPosition(float x, float y)
    {
        m_AnalogState[(InputId)MouseInputId::CursorX] = x;
        m_AnalogState[(InputId)MouseInputId::CursorY] = y;
    }

}
