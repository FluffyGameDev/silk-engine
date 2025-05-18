#include <silk/engine/engine.h>

#include <silk/engine/window/application_window_config.h>
#include <silk/engine/window/application_window_inputs.h>

namespace silk
{
    Engine::Engine(const EngineConfig& config)
        : m_EngineConfig{ config }
        , m_MainWindow{}
        , m_GraphicsContext{}
        , m_DebugToolbox{}
        , m_FrameRateTimer{ config.targetFps }
    {
    }

    void Engine::Run()
    {
        Init();

        ApplicationWindowInputs mainWindowInputs{};
        while (!mainWindowInputs.shouldCloseWindow)
        {
            RunFrame(mainWindowInputs);
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
        m_FrameRateTimer.StartFrame();
        m_DebugToolbox.StartFrame();
        m_MainWindow.PollInputs(windowInputs);

        //Update

        m_GraphicsContext.Render();
        m_DebugToolbox.EndFrame();

        m_MainWindow.SwapBuffer();
        m_FrameRateTimer.EndFrame();
    }
}
