#pragma once

#include <silk/core/slot.h>
#include <silk/engine/input/input_device.h>

namespace silk
{

    class KeyboardDevice : public InputDevice
    {
    public:
        void Init(ApplicationWindow& window);
        void Shutdown(ApplicationWindow& window);

    private:
        void OnkeyInput(InputId inputId, bool isPressed);

        Slot<void(InputId, bool)> m_OnKeyInputSlot;
    };

}
