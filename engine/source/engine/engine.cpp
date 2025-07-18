#include <silk/engine/engine.h>

#include <algorithm>

#include <silk/engine/module/module_entry_points.h>
#include <silk/engine/service/service.h>
#include <silk/engine/time/time.h>
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

    void Engine::PreInstallModule(ModuleEntryPoints* moduleEntryPoints)
    {
        m_Modules.push_back(moduleEntryPoints);
    }

    void Engine::RegisterService(Service* service)
    {
        m_Services.push_back(service);
    }

    void Engine::UnregisterService(Service* service)
    {
        auto endIt{ m_Services.end() };
        auto removeIt{ std::remove(m_Services.begin(), endIt, service)};
        if (removeIt != endIt)
        {
            m_Services.erase(removeIt, endIt);
        }
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
        time::StartEngine();

        ApplicationWindowConfig mainWindowConfig
        {
            .width = 800,
            .heigth = 600,
            .windowTitle = "Silk"
        };

        m_MainWindow.Init(mainWindowConfig);
        m_InputService.Init();
        m_GraphicsContext.Init();
        m_DebugToolbox.Init(m_MainWindow);

        for (ModuleEntryPoints* moduleEntryPoints : m_Modules)
        {
            moduleEntryPoints->Install(*this);
        }

        for (Service* service : m_Services)
        {
            service->Init(*this);
        }
    }

    void Engine::Shutdown()
    {
        for (auto serviceIt = m_Services.rbegin(); serviceIt != m_Services.rend(); ++serviceIt)
        {
            (*serviceIt)->Shutdown(*this);
        }

        for (auto moduleIt = m_Modules.rbegin(); moduleIt != m_Modules.rend(); ++moduleIt)
        {
            (*moduleIt)->Uninstall(*this);
        }

        m_DebugToolbox.Shutdown();
        m_GraphicsContext.Shutdown();
        m_InputService.Shutdown();
        m_MainWindow.Shutdown();
    }

    void Engine::RunFrame(ApplicationWindowInputs& windowInputs)
    {
        m_FrameRateTimer.StartFrame();
        m_DebugToolbox.StartFrame();
        m_InputService.SwapStateBuffers();
        m_MainWindow.PollInputs(windowInputs);
        m_InputService.GetInputActionWatcher().Update(m_InputService);

        m_UpdateSignal.Raise();
        m_GraphicsContext.Render();

        m_DebugToolbox.EndFrame();

        m_MainWindow.SwapBuffer();
        m_FrameRateTimer.EndFrame();
    }
}
