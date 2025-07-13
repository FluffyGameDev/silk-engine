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
            m_Devices.clear();
        }
    }

    void InputService::SwapStateBuffers()
    {
        for (auto& device : m_Devices)
        {
            device.second->SwapStateBuffers();
        }

        m_InputActionWatcher.Update(*this);
    }

    float InputService::GetAnalogState(InputDeviceId deviceId, InputId inputId) const
    {
        return m_Devices.at(deviceId.deviceId)->GetAnalogState(inputId);
    }

    bool InputService::IsButtonDown(InputDeviceId deviceId, InputId inputId) const
    {
        return m_Devices.at(deviceId.deviceId)->GetButtonState(inputId);
    }

    bool InputService::IsButtonPressed(InputDeviceId deviceId, InputId inputId) const
    {
        const InputDevice* device{ m_Devices.at(deviceId.deviceId) };
        return device->GetButtonState(inputId) && !device->GetButtonPreviousState(inputId);
    }

    bool InputService::IsButtonReleased(InputDeviceId deviceId, InputId inputId) const
    {
        const InputDevice* device{ m_Devices.at(deviceId.deviceId) };
        return !device->GetButtonState(inputId) && device->GetButtonPreviousState(inputId);
    }

    void InputService::RegisterDevice(InputDevice& device)
    {
        for (auto& entry : m_Devices)
        {
            if (entry.second->m_DeviceId.data.deviceType == device.m_DeviceId.data.deviceType)
            {
                device.m_DeviceId.data.deviceNumber = std::max<u8>(device.m_DeviceId.data.deviceNumber, entry.second->m_DeviceId.data.deviceNumber + 1);
            }
        }

        m_Devices.emplace(device.m_DeviceId.deviceId, &device);
    }

    void InputService::UnregisterDevice(InputDevice& device)
    {
        m_Devices.erase(device.m_DeviceId.deviceId);
    }

}
