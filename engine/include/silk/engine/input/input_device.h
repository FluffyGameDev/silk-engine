#pragma once

#include <silk/core/signal.h>
#include <silk/engine/input/input_types.h>

namespace silk
{
    class ApplicationWindow;

    class InputDevice
    {
    public:
        InputDevice() = default;
        virtual ~InputDevice() = default;

    protected:
        Signal<void(InputId, float)> m_AnalogInputStateChanged;
        Signal<void(InputId, bool)> m_ButtonInputStateChanged;
        InputDeviceId m_DeviceId;

        friend class InputService;
    };

}
