#pragma once

namespace silk
{
    class ApplicationWindow;

    class DebugToolbox
    {
    public:
        void Init(ApplicationWindow& applicationWindow);
        void Shutdown();

        void StartFrame();
        void EndFrame();
    };
}
