#pragma once

#if defined(SILK_ENABLE_PROFILER)

#include <chrono>
#include <type_traits>

#include <silk/core/steady_clock.h>

namespace silk
{
    class ProfilingScopedTimer
    {
    public:
        ProfilingScopedTimer(const char* timerName);
        ~ProfilingScopedTimer();

    private:
        const char* m_TimerName;
        std::chrono::time_point<SteadyClock> m_StartTime;
    };
}

#define SILK_SCOPED_PROFILE(name) silk::ProfilingScopedTimer scopedTime_##name##{ #name }

#else

#define SILK_SCOPED_PROFILE(name)

#endif // defined(SILK_ENABLE_PROFILER)
