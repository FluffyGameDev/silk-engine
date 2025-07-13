#include <silk/engine/input/actions/input_action.h>

namespace silk
{

    void InputAction::ConfigureAnalog()
    {
        m_InputActionType = InputActionType::Analog;
        m_ButtonInputActionEvent = ButtonInputActionEvent::None;
    }

    void InputAction::ConfigureButton(ButtonInputActionEvent buttonEvent /*= ButtonInputActionEvent::None*/, float eventDuration /*= 0.0f*/)
    {
        m_InputActionType = InputActionType::Button;
        m_ButtonInputActionEvent = buttonEvent;
        m_EventDuration = eventDuration;
    }

    void InputAction::AddSettings(InputDeviceId deviceId, InputId inputId)
    {
        m_Settings.emplace_back(deviceId, inputId);
    }

}
