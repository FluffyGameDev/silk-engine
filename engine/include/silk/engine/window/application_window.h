#pragma once

#include <silk/core/types.h>

struct GLFWwindow;

namespace silk
{
    struct ApplicationWindowConfig;
    struct ApplicationWindowInputs;

    class ApplicationWindow
    {
    public:
        void Init(ApplicationWindowConfig& config);
        void Shutdown();

        void SwapBuffer();
        void PollInputs(ApplicationWindowInputs& inputs);

    private:
        GLFWwindow* m_Window;
    };
}
