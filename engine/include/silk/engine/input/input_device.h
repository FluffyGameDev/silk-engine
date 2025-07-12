#pragma once

#include <silk/core/signal.h>
#include <silk/engine/input/input_types.h>

namespace silk
{
    class ApplicationWindow;

    class InputDevice
    {
    public:
        virtual ~InputDevice() = default;

        Signal<void(InputId, float)>& GetAnalogInputStateChanged() { return m_AnalogInputStateChanged; }
        Signal<void(InputId, bool)>& GetButtonInputStateChanged() { return m_ButtonInputStateChanged; }

    protected:
        Signal<void(InputId, float)> m_AnalogInputStateChanged;
        Signal<void(InputId, bool)> m_ButtonInputStateChanged;
    };

}
