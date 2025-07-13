#pragma once

#include <unordered_map>

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

        float GetAnalogState(InputDeviceId deviceId, InputId inputId) const;

        bool IsButtonDown(InputDeviceId deviceId, InputId inputId) const;
        bool IsButtonPressed(InputDeviceId deviceId, InputId inputId) const;
        bool IsButtonReleased(InputDeviceId deviceId, InputId inputId) const;

        void RegisterDevice(InputDevice& device);
        void UnregisterDevice(InputDevice& device);

    private:
        InputActionWatcher m_InputActionWatcher;
        std::unordered_map<u16, InputDevice*> m_Devices;
    };

}
