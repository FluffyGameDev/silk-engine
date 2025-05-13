#include <silk/engine/engine.h>

#include <chrono>
#include <thread>

#include <silk/core/steady_clock.h>
#include <silk/engine/engine_config.h>
#include <silk/engine/debug/debug_toolbox.h>
#include <silk/engine/graphics/graphics_context.h>
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

        GraphicsContext graphicsContext{};
        graphicsContext.Init();

        DebugToolbox debugToolbox{};
        debugToolbox.Init(mainWindow);

        ApplicationWindowInputs mainWindowInputs{};
        while (!mainWindowInputs.shouldCloseWindow)
        {
            auto frameStartTime = SteadyClock::now();

            debugToolbox.StartFrame();
            mainWindow.PollInputs(mainWindowInputs);

            //Update

            graphicsContext.Render();
            debugToolbox.EndFrame();

            mainWindow.SwapBuffer();

            auto frameDuration{ std::chrono::duration_cast<decltype(targetFrameLength)>(SteadyClock::now() - frameStartTime)};
            if (frameDuration < targetFrameLength)
            {
                std::this_thread::sleep_for(targetFrameLength - frameDuration);
            }
        }

        graphicsContext.Shutdown();
        mainWindow.Shutdown();
    }
}
