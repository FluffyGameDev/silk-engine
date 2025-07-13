#pragma once

#include <bitset>

#include <silk/core/slot.h>
#include <silk/engine/input/input_device.h>

namespace silk
{

    class KeyboardDevice : public InputDevice
    {
    public:
        KeyboardDevice();

        void Init(ApplicationWindow& window);
        void Shutdown(ApplicationWindow& window);

        void SwapStateBuffers() override;

        float GetAnalogState(InputId inputId) const override;
        bool GetButtonState(InputId inputId) const override;
        bool GetButtonPreviousState(InputId inputId) const override;

    private:
        void OnKeyInput(InputId inputId, bool isPressed);

        static constexpr size_t INPUT_STATE_BUFFER_COUNT{ 2 };

        std::bitset<static_cast<size_t>(KeyboardInputId::Count)> m_InputStates[INPUT_STATE_BUFFER_COUNT];
        size_t m_CurrentInputStateIndex;

        Slot<void(InputId, bool)> m_OnKeyInputSlot;
    };

}
