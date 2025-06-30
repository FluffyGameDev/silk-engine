#pragma once

namespace silk
{
    class GraphicsContext
    {
    public:
        void Init();
        void Shutdown();

        void StartFrame();
        void EndFrame();

    private:
    };
}
