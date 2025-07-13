#include <silk/engine/input/actions/input_action_watcher.h>

#include <silk/engine/input/actions/input_action.h>

namespace silk
{

    void InputActionWatcher::RegisterInputAction(const InputAction& inputAction)
    {
        m_InputActionStates.emplace(&inputAction, std::make_unique<InputActionState>(&inputAction));
    }

    void InputActionWatcher::UnregisterInputAction(const InputAction& inputAction)
    {
        m_InputActionStates.erase(&inputAction);
    }

    void InputActionWatcher::Update(const InputService& inputService)
    {
        for (const auto& state : m_InputActionStates)
        {
            state.second->Update(inputService);
        }
    }

    float InputActionWatcher::GetAnalogState(const InputAction& inputAction) const
    {
        return m_InputActionStates.at(&inputAction)->GetAnalogState();
    }

    bool InputActionWatcher::GetButtonState(const InputAction& inputAction) const
    {
        return m_InputActionStates.at(&inputAction)->GetButtonState();
    }

    InputActionState* InputActionWatcher::GetInputActionState(const InputAction& inputAction)
    {
        return m_InputActionStates.at(&inputAction).get();
    }

    const InputActionState* InputActionWatcher::GetInputActionState(const InputAction& inputAction) const
    {
        return m_InputActionStates.at(&inputAction).get();
    }

}
