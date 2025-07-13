#pragma once

#include <memory>
#include <unordered_map>

#include <silk/engine/input/actions/input_action_state.h>

namespace silk
{

    class InputAction;
    class InputActionState;

    class InputActionWatcher
    {
    public:
        void RegisterInputAction(const InputAction& inputAction);
        void UnregisterInputAction(const InputAction& inputAction);

        void Update(const InputService& inputService);

        float GetAnalogState(const InputAction& inputAction) const;
        bool GetButtonState(const InputAction& inputAction) const;

        InputActionState* GetInputActionState(const InputAction& inputAction);
        const InputActionState* GetInputActionState(const InputAction& inputAction) const;

    private:
        std::unordered_map<const InputAction*, std::unique_ptr<InputActionState>> m_InputActionStates;
    };

}
