#include <silk/engine/frame_rate/frame_rate_timer.h>

#include <thread>

#include <silk/core/assert.h>

namespace silk
{
    FrameRateTimer::FrameRateTimer(u32 targetFps)
        : m_TargetFrameLength{ 1000000LL / static_cast<typename std::chrono::microseconds::rep>(targetFps) }
        , m_FrameStartTime{}
        , m_IsFrameInProgress{}
    {
    }

    void FrameRateTimer::StartFrame()
    {
        SILK_ASSERT(!m_IsFrameInProgress, "Frame should not already be in progress when starting.");
        m_IsFrameInProgress = true;

        m_FrameStartTime = SteadyClock::now();
    }

    void FrameRateTimer::EndFrame()
    {
        SILK_ASSERT(m_IsFrameInProgress, "Frame should be in progress when ending.");
        m_IsFrameInProgress = false;

        auto frameDuration{ std::chrono::duration_cast<decltype(m_TargetFrameLength)>(SteadyClock::now() - m_FrameStartTime) };
        if (frameDuration < m_TargetFrameLength)
        {
            std::this_thread::sleep_for(m_TargetFrameLength - frameDuration);
        }
    }
}
