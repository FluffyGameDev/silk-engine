#include <silk/engine/input/actions/input_action_state.h>

#include <silk/core/assert.h>
#include <silk/engine/input/input_service.h>
#include <silk/engine/input/actions/input_action.h>
#include <silk/engine/time/time.h>

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

    float InputActionState::GetEllapsedTime() const
    {
        SILK_ASSERT(m_InputAction->GetInputActionType() == InputActionType::Button, "Can't measure ellapsed time for button input actions.");
        return time::GetTime() - m_AnalogState;
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
                    bool buttonState{};
                    for (const InputActionSettings& settings : m_InputAction->GetSettings())
                    {
                        buttonState |= inputService.IsButtonDown(settings.inputId);
                    }

                    if (m_CurrentEventStep == ButtonInputActionEventStep::Idle)
                    {
                        if (buttonState)
                        {
                            m_AnalogState = time::GetTime();
                            m_CurrentEventStep = ButtonInputActionEventStep::InProgress;
                        }
                    }
                    else if (m_CurrentEventStep == ButtonInputActionEventStep::InProgress)
                    {
                        if (!buttonState)
                        {
                            bool isValidated{ GetEllapsedTime() < m_InputAction->GetEventDuration() };
                            m_CurrentEventStep = isValidated ? ButtonInputActionEventStep::Validate : ButtonInputActionEventStep::Cancel;
                        }
                    }
                    else
                    {
                        m_CurrentEventStep = ButtonInputActionEventStep::Idle;
                    }

                    triggerEvent = (m_CurrentEventStep == ButtonInputActionEventStep::Validate);
                    break;
                }
                case ButtonInputActionEvent::Hold:
                {
                    bool buttonState{};
                    for (const InputActionSettings& settings : m_InputAction->GetSettings())
                    {
                        buttonState |= inputService.IsButtonDown(settings.inputId);
                    }

                    if (m_CurrentEventStep == ButtonInputActionEventStep::Idle)
                    {
                        if (buttonState)
                        {
                            m_AnalogState = time::GetTime();
                            m_CurrentEventStep = ButtonInputActionEventStep::InProgress;
                        }
                    }
                    else if (m_CurrentEventStep == ButtonInputActionEventStep::InProgress)
                    {
                        if (!buttonState)
                        {
                            m_CurrentEventStep = ButtonInputActionEventStep::Cancel;
                        }
                        else
                        {
                            if (GetEllapsedTime() >= m_InputAction->GetEventDuration())
                            {
                                m_CurrentEventStep = ButtonInputActionEventStep::Validate;
                            }
                        }
                    }
                    else
                    {
                        m_CurrentEventStep = ButtonInputActionEventStep::Idle;
                    }

                    triggerEvent = (m_CurrentEventStep == ButtonInputActionEventStep::Validate);
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
