#pragma once

#include <bitset>
#include <memory>
#include <vector>

#include <silk/core/slot.h>
#include <silk/engine/input/input_device.h>
#include <silk/engine/input/actions/input_action_watcher.h>

namespace silk
{
    class ApplicationWindow;

    class InputService
    {
    public:
        InputService() = default;

        void Init();
        void Shutdown();

        void SwapStateBuffers();

        inline InputActionWatcher& GetInputActionWatcher() { return m_InputActionWatcher; }

        bool IsButtonDown(InputId inputId) const;
        bool IsButtonPressed(InputId inputId) const;
        bool IsButtonReleased(InputId inputId) const;

        void RegisterDevice(InputDevice& device);
        void UnregisterDevice(InputDevice& device);

    private:
        void OnAnalogInputStateChanged(InputId inputId, float state);
        void OnButtonInputStateChanged(InputId inputId, bool isPressed);

        struct InputDeviceEntry
        {
            InputDeviceEntry() = default;
            ~InputDeviceEntry();

            InputDevice* device;
            Slot<void(InputId, float)> analogInputStateChangedSlot;
            Slot<void(InputId, bool)> buttonInputStateChangedSlot;
        };

        static constexpr size_t INPUT_STATE_BUFFER_COUNT{ 2 };

        InputActionWatcher m_InputActionWatcher;
        std::vector<std::unique_ptr<InputDeviceEntry>> m_Devices;
        std::bitset<static_cast<size_t>(InputId::Count)> m_InputStates[INPUT_STATE_BUFFER_COUNT];
        size_t m_CurrentInputStateIndex;
    };

}
