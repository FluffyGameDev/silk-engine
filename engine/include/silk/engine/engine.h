#pragma once

#include <silk/core/signal.h>
#include <silk/engine/engine_config.h>
#include <silk/engine/debug/debug_toolbox.h>
#include <silk/engine/graphics/graphics_context.h>
#include <silk/engine/frame_rate/frame_rate_timer.h>
#include <silk/engine/window/application_window.h>

#include <vector>

namespace silk
{
    class ModuleEntryPoints;
    class Service;
    struct EngineConfig;

    class Engine
    {
    public:
        Engine(const EngineConfig& config);

        void PreInstallModule(ModuleEntryPoints* moduleEntryPoints);

        void RegisterService(Service* service);
        void UnregisterService(Service* service);

        void Run();

        inline DebugToolbox& GetDebugToolbox() { return m_DebugToolbox; }

        inline Signal<void()>& GetUpdateSignal() { return m_UpdateSignal; }
        inline Signal<void(GraphicsContext&)>& GetDrawSignal() { return m_DrawSignal; }

    private:
        void Init();
        void Shutdown();
        void RunFrame(ApplicationWindowInputs& windowInputs);

        EngineConfig m_EngineConfig;

        ApplicationWindow m_MainWindow;
        GraphicsContext m_GraphicsContext;
        DebugToolbox m_DebugToolbox;
        FrameRateTimer m_FrameRateTimer;

        Signal<void()> m_UpdateSignal;
        Signal<void(GraphicsContext&)> m_DrawSignal;

        std::vector<ModuleEntryPoints*> m_Modules;
        std::vector<Service*> m_Services;
    };
}
