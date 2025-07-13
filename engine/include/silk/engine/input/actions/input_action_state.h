#pragma once

#include <silk/core/signal.h>
#include <silk/core/types.h>

namespace silk
{

    class InputAction;
    class InputService;

    enum class ButtonInputActionEventStep : u8;

    class InputActionState
    {
    public:
        InputActionState(const InputAction* m_InputAction);

        void Update(const InputService& inputService);

        inline const InputAction* GetInputAction() const { return m_InputAction; }

        inline float GetAnalogState() const { return m_AnalogState; }
        inline bool GetButtonState() const { return m_ButtonState; }

        inline Signal<void(const InputActionState&)>& GetButtonEventSignal() { return m_ButtonEventSignal; }
        inline ButtonInputActionEventStep GetCurrentEventStep() const { return m_CurrentEventStep; }

    private:
        const InputAction* m_InputAction;
        Signal<void(const InputActionState&)> m_ButtonEventSignal;
        float m_AnalogState;
        ButtonInputActionEventStep m_CurrentEventStep;
        bool m_ButtonState;
    };

}
