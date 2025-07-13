#pragma once

#include <silk/core/signal.h>
#include <silk/core/types.h>
#include <silk/engine/input/input_types.h>

struct GLFWwindow;

namespace silk
{
    struct ApplicationWindowConfig;
    struct ApplicationWindowInputs;

    enum class InputState;

    class ApplicationWindow
    {
    public:
        void Init(ApplicationWindowConfig& config);
        void Shutdown();

        void SwapBuffer();
        void PollInputs(ApplicationWindowInputs& inputs);

        inline GLFWwindow* GetWindow() { return m_Window; }

        inline Signal<void(InputId, bool)>& GetKeyboardInputSignal() { return m_KeyboardInputSignal; }
        inline Signal<void(InputId, bool)>& GetMouseInputSignal() { return m_MouseInputSignal; }
        inline Signal<void(float, float)>& GetCursorPositionSignal() { return m_CursorPositionSignal; }

    private:
        GLFWwindow* m_Window;
        Signal<void(InputId, bool)> m_KeyboardInputSignal;
        Signal<void(InputId, bool)> m_MouseInputSignal;
        Signal<void(float, float)> m_CursorPositionSignal;
    };
}
