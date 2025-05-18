#pragma once

#include <chrono>

#include <silk/core/steady_clock.h>
#include <silk/core/types.h>

namespace silk
{
    class FrameRateTimer
    {
    public:
        FrameRateTimer(u32 targetFps);

        void StartFrame();
        void EndFrame();

    private:
        std::chrono::microseconds m_TargetFrameLength;
        SteadyClock::time_point m_FrameStartTime;
        bool m_IsFrameInProgress;
    };
}
