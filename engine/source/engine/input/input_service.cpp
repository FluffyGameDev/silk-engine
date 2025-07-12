#include <silk/engine/input/input_service.h>

#include <silk/core/log.h>
#include <silk/core/log_categories.h>
#include <silk/engine/input/input_device.h>

namespace silk
{
    void InputService::Init()
    {
    }

    void InputService::Shutdown()
    {
        if (!m_Devices.empty())
        {
            SILK_LOG_ERROR(LogInput, "Not all input devices were unregistered.");
        }
    }

    void InputService::RegisterDevice(InputDevice& device)
    {
        m_Devices.push_back(&device);
    }

    void InputService::UnregisterDevice(InputDevice& device)
    {
        auto endIt{ m_Devices.end() };
        auto remIt{ std::remove(m_Devices.begin(), endIt, &device) };
        if (remIt != endIt)
        {
            m_Devices.erase(remIt, endIt);
        }
    }

}
