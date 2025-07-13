#include <silk/engine/input/input_service.h>

#include <silk/core/log.h>
#include <silk/core/log_categories.h>
#include <silk/engine/input/input_device.h>

namespace silk
{

    void InputService::Init()
    {
        m_CurrentInputStateIndex = 0;
        for (size_t i = 0; i < INPUT_STATE_BUFFER_COUNT; ++i)
        {
            m_InputStates[i] = {};
        }
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
        const auto& prevState{ m_InputStates[m_CurrentInputStateIndex] };
        m_CurrentInputStateIndex = (m_CurrentInputStateIndex + 1) % INPUT_STATE_BUFFER_COUNT;
        m_InputStates[m_CurrentInputStateIndex] = prevState;

        m_InputActionWatcher.Update(*this);
    }

    bool InputService::IsButtonDown(InputId inputId) const
    {
        return m_InputStates[m_CurrentInputStateIndex].test(static_cast<size_t>(inputId));
    }

    bool InputService::IsButtonPressed(InputId inputId) const
    {
        bool curState{ m_InputStates[m_CurrentInputStateIndex].test(static_cast<size_t>(inputId)) };
        bool prevState{ m_InputStates[(m_CurrentInputStateIndex + 1) % INPUT_STATE_BUFFER_COUNT].test(static_cast<size_t>(inputId)) };
        return curState && !prevState;
    }

    bool InputService::IsButtonReleased(InputId inputId) const
    {
        bool curState{ m_InputStates[m_CurrentInputStateIndex].test(static_cast<size_t>(inputId)) };
        bool prevState{ m_InputStates[(m_CurrentInputStateIndex + 1) % INPUT_STATE_BUFFER_COUNT].test(static_cast<size_t>(inputId)) };
        return !curState && prevState;
    }

    void InputService::RegisterDevice(InputDevice& device)
    {
        for (const auto& entry : m_Devices)
        {
            if (entry->device->m_DeviceId.data.deviceType == device.m_DeviceId.data.deviceType)
            {
                device.m_DeviceId.data.deviceNumber = std::max<u8>(device.m_DeviceId.data.deviceNumber, entry->device->m_DeviceId.data.deviceNumber + 1);
            }
        }

        auto& entry{ m_Devices.emplace_back() };
        entry = std::make_unique<InputDeviceEntry>();
        entry->device = &device;
        entry->analogInputStateChangedSlot.SetBoundFunction([this](InputId inputId, float state) { OnAnalogInputStateChanged(inputId, state); });
        entry->buttonInputStateChangedSlot.SetBoundFunction([this](InputId inputId, bool isPressed) { OnButtonInputStateChanged(inputId, isPressed); });

        device.m_AnalogInputStateChanged.Connect(entry->analogInputStateChangedSlot);
        device.m_ButtonInputStateChanged.Connect(entry->buttonInputStateChangedSlot);
    }

    void InputService::UnregisterDevice(InputDevice& device)
    {
        auto endIt{ m_Devices.end() };
        auto foundit{ std::find_if(m_Devices.begin(), endIt,
            [&device](const auto& entry) { return entry->device == &device; }) };
        if (foundit != endIt)
        {
            device.m_ButtonInputStateChanged.Disconnect((*foundit)->buttonInputStateChangedSlot);
            device.m_AnalogInputStateChanged.Disconnect((*foundit)->analogInputStateChangedSlot);
            m_Devices.erase(foundit);
        }
    }


    void InputService::OnAnalogInputStateChanged(InputId /*inputId*/, float /*state*/)
    {
        //TODO
    }

    void InputService::OnButtonInputStateChanged(InputId inputId, bool isPressed)
    {
        m_InputStates[m_CurrentInputStateIndex].set(static_cast<size_t>(inputId), isPressed);
    }



    InputService::InputDeviceEntry::~InputDeviceEntry()
    {
        device->m_AnalogInputStateChanged.Disconnect(analogInputStateChangedSlot);
        device->m_ButtonInputStateChanged.Disconnect(buttonInputStateChangedSlot);
    }

}
