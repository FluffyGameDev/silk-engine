#pragma once

#include <bitset>
#include <unordered_map>

#include <silk/core/slot.h>
#include <silk/engine/input/input_device.h>

namespace silk
{

    class MouseDevice : public InputDevice
    {
    public:
        MouseDevice();

        void Init(ApplicationWindow& window);
        void Shutdown(ApplicationWindow& window);

        void SwapStateBuffers() override;

        float GetAnalogState(InputId inputId) const override;
        bool GetButtonState(InputId inputId) const override;
        bool GetButtonPreviousState(InputId inputId) const override;

    private:
        void OnMouseInput(InputId inputId, bool isPressed);
        void OnOnCursorPosition(float x, float y);

        static constexpr size_t INPUT_STATE_BUFFER_COUNT{ 2 };

        std::bitset<static_cast<size_t>(MouseInputId::Count)> m_InputStates[INPUT_STATE_BUFFER_COUNT];
        size_t m_CurrentInputStateIndex;

        std::unordered_map<InputId, float> m_AnalogState;

        Slot<void(InputId, bool)> m_OnMouseInputSlot;
        Slot<void(float, float)> m_OnCursorPositionSlot;
    };

}
