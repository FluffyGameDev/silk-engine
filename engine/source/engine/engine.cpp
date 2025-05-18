#include <silk/engine/engine.h>

#include <chrono>
#include <thread>

#include <silk/core/steady_clock.h>
#include <silk/engine/window/application_window_config.h>
#include <silk/engine/window/application_window_inputs.h>

namespace silk
{
    Engine::Engine(const EngineConfig& config)
        : m_EngineConfig{ config }
        , m_MainWindow{}
        , m_GraphicsContext{}
        , m_DebugToolbox{}
    {
    }

    void Engine::Run()
    {
        std::chrono::microseconds targetFrameLength{ 1000000LL / static_cast<typename std::chrono::microseconds::rep>(m_EngineConfig.targetFps) };

        Init();

        ApplicationWindowInputs mainWindowInputs{};
        while (!mainWindowInputs.shouldCloseWindow)
        {
            auto frameStartTime = SteadyClock::now();

            RunFrame(mainWindowInputs);

            auto frameDuration{ std::chrono::duration_cast<decltype(targetFrameLength)>(SteadyClock::now() - frameStartTime) };
            if (frameDuration < targetFrameLength)
            {
                std::this_thread::sleep_for(targetFrameLength - frameDuration);
            }
        }

        Shutdown();
    }

    void Engine::Init()
    {
        ApplicationWindowConfig mainWindowConfig
        {
            .width = 800,
            .heigth = 600,
            .windowTitle = "Silk"
        };

        m_MainWindow.Init(mainWindowConfig);
        m_GraphicsContext.Init();
        m_DebugToolbox.Init(m_MainWindow);
    }

    void Engine::Shutdown()
    {
        m_DebugToolbox.Shutdown();
        m_GraphicsContext.Shutdown();
        m_MainWindow.Shutdown();
    }

    void Engine::RunFrame(ApplicationWindowInputs& windowInputs)
    {
        m_DebugToolbox.StartFrame();
        m_MainWindow.PollInputs(windowInputs);

        //Update

        m_GraphicsContext.Render();
        m_DebugToolbox.EndFrame();

        m_MainWindow.SwapBuffer();
    }
}
