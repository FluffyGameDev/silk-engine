#pragma once

#include <memory>
#include <vector>

#include <silk/engine/input/input_device.h>

namespace silk
{
    class ApplicationWindow;

    class InputService
    {
    public:
        void Init();
        void Shutdown();

        void RegisterDevice(InputDevice& device);
        void UnregisterDevice(InputDevice& device);

    private:
        std::vector<InputDevice*> m_Devices;
        ApplicationWindow* m_Window;
    };

}
