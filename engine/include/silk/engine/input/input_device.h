#pragma once

#include <silk/engine/input/input_types.h>

namespace silk
{
    class ApplicationWindow;

    class InputDevice
    {
    public:
        virtual ~InputDevice() = default;

        virtual void SwapStateBuffers() = 0;

        virtual float GetAnalogState(InputId inputId) const = 0;
        virtual bool GetButtonState(InputId inputId) const = 0;
        virtual bool GetButtonPreviousState(InputId inputId) const = 0;

        InputDeviceId GetDeviceId() const { return m_DeviceId; }

    protected:
        InputDeviceId m_DeviceId;

        friend class InputService;
    };

}
