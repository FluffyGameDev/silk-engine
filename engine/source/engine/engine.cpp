#include <silk/engine/engine.h>

#include <chrono>
#include <thread>

#include <silk/core/steady_clock.h>
#include <silk/engine/engine_config.h>
#include <silk/engine/window/application_window.h>
#include <silk/engine/window/application_window_config.h>
#include <silk/engine/window/application_window_inputs.h>

namespace silk
{
    void RunEngine(const EngineConfig& config)
    {
        std::chrono::microseconds targetFrameLength{ 1000000LL / static_cast<typename std::chrono::microseconds::rep>(config.targetFps) };

        ApplicationWindowConfig mainWindowConfig
        {
            .width = 800,
            .heigth = 600,
            .windowTitle = "Silk"
        };

        ApplicationWindow mainWindow{};
        mainWindow.Init(mainWindowConfig);

        ApplicationWindowInputs mainWindowInputs{};
        while (!mainWindowInputs.shouldCloseWindow)
        {
            auto frameStartTime = SteadyClock::now();

            mainWindow.PollInputs(mainWindowInputs);

            //Update
            //Render

            mainWindow.SwapBuffer();

            auto frameDuration{ std::chrono::duration_cast<decltype(targetFrameLength)>(SteadyClock::now() - frameStartTime)};
            if (frameDuration < targetFrameLength)
            {
                std::this_thread::sleep_for(targetFrameLength - frameDuration);
            }
        }

        mainWindow.Shutdown();
    }
}
