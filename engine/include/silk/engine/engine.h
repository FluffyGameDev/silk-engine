#pragma once

#include <silk/engine/engine_config.h>
#include <silk/engine/debug/debug_toolbox.h>
#include <silk/engine/graphics/graphics_context.h>
#include <silk/engine/window/application_window.h>

namespace silk
{
    struct EngineConfig;

    class Engine
    {
    public:
        Engine(const EngineConfig& config);

        void Run();

    private:
        void Init();
        void Shutdown();
        void RunFrame(ApplicationWindowInputs& windowInputs);

        EngineConfig m_EngineConfig;

        ApplicationWindow m_MainWindow;
        GraphicsContext m_GraphicsContext;
        DebugToolbox m_DebugToolbox;
    };
}
