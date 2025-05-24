#pragma once

#include <vector>

namespace silk
{
    class ApplicationWindow;
    class DebugTool;

    class DebugToolbox
    {
    public:
        void RegisterTool(DebugTool* tool);
        void UnregisterTool(DebugTool* tool);

    private:
        void Init(ApplicationWindow& applicationWindow);
        void Shutdown();

        void StartFrame();
        void EndFrame();

        std::vector<DebugTool*> m_DebugTools;

        friend class Engine;
    };
}
