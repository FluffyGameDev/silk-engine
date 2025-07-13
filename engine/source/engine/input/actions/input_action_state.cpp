#include <silk/engine/input/actions/input_action_state.h>

#include <silk/engine/input/input_service.h>
#include <silk/engine/input/actions/input_action.h>

namespace silk
{

    InputActionState::InputActionState(const InputAction* m_InputAction)
        : m_InputAction{ m_InputAction }
        , m_ButtonEventSignal{}
        , m_AnalogState{}
        , m_CurrentEventStep{}
        , m_ButtonState{}
    {
    }

    void InputActionState::Update(const InputService& inputService)
    {
        InputActionType actionType{ m_InputAction->GetInputActionType() };
        if (actionType == InputActionType::Analog)
        {
            // TODO
        }
        else if (actionType == InputActionType::Button)
        {
            ButtonInputActionEvent buttonEvent{ m_InputAction->GetButtonInputActionEvent() };
            bool triggerEvent{};

            switch (buttonEvent)
            {
                case ButtonInputActionEvent::None:
                {
                    m_ButtonState = false;
                    for (const InputActionSettings& settings : m_InputAction->GetSettings())
                    {
                        m_ButtonState |= inputService.IsButtonDown(settings.inputId);
                    }
                    break;
                }
                case ButtonInputActionEvent::Press:
                {
                    m_ButtonState = false;
                    for (const InputActionSettings& settings : m_InputAction->GetSettings())
                    {
                        m_ButtonState |= inputService.IsButtonPressed(settings.inputId);
                    }
                    triggerEvent = m_ButtonState;
                    m_CurrentEventStep = m_ButtonState ? ButtonInputActionEventStep::Validate : ButtonInputActionEventStep::Idle;
                    break;
                }
                case ButtonInputActionEvent::Release:
                {
                    m_ButtonState = false;
                    for (const InputActionSettings& settings : m_InputAction->GetSettings())
                    {
                        m_ButtonState |= inputService.IsButtonReleased(settings.inputId);
                    }
                    triggerEvent = m_ButtonState;
                    m_CurrentEventStep = m_ButtonState ? ButtonInputActionEventStep::Validate : ButtonInputActionEventStep::Idle;
                    break;
                }
                case ButtonInputActionEvent::Tap:
                {
                    //TODO
                    break;
                }
                case ButtonInputActionEvent::Hold:
                {
                    //TODO
                    break;
                }
            }

            if (triggerEvent)
            {
                m_ButtonEventSignal.Raise(*this);
            }
        }
    }

}
