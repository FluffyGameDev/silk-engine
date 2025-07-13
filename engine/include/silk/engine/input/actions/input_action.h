#pragma once

#include <vector>

#include <silk/engine/input/input_types.h>

namespace silk
{

    enum class InputActionType : u8
    {
        Analog,
        Button,
    };

    enum class ButtonInputActionEvent : u8
    {
        None,
        Press,
        Release,
        Tap,
        Hold,
    };

    enum class ButtonInputActionEventStep : u8
    {
        Idle,
        InProgress,
        Validate,
        Cancel,
    };

    struct InputActionSettings
    {
        InputDeviceId deviceId;
        InputId inputId;
        //TODO: handle combos
    };

    class InputAction
    {
    public:
        void ConfigureAnalog();
        void ConfigureButton(ButtonInputActionEvent buttonEvent = ButtonInputActionEvent::None, float eventDuration = 0.5f);

        void AddSettings(InputDeviceId deviceId, InputId inputId);

        inline const std::vector<InputActionSettings>& GetSettings() const { return m_Settings; }
        inline InputActionType GetInputActionType() const { return m_InputActionType; }

        inline ButtonInputActionEvent GetButtonInputActionEvent() const { return m_ButtonInputActionEvent; }
        inline float GetEventDuration() const { return m_EventDuration; }

    private:
        std::vector<InputActionSettings> m_Settings;
        float m_EventDuration;
        InputActionType m_InputActionType;
        ButtonInputActionEvent m_ButtonInputActionEvent;
    };

}
