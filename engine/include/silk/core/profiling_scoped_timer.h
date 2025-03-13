#pragma once

#if defined(SILK_ENABLE_PROFILER)

#include <chrono>
#include <type_traits>

namespace silk
{
    class ProfilingScopedTimer
    {
    public:
        ProfilingScopedTimer(const char* timerName);
        ~ProfilingScopedTimer();

    private:
        using ProfilingClock = typename std::conditional<std::chrono::high_resolution_clock::is_steady,
            std::chrono::high_resolution_clock, std::chrono::steady_clock>::type;

        const char* m_TimerName;
        std::chrono::time_point<ProfilingClock> m_StartTime;
    };
}

#define SILK_SCOPED_PROFILE(name) silk::ProfilingScopedTimer scopedTime_##name##{ #name }

#else

#define SILK_SCOPED_PROFILE(name)

#endif // defined(SILK_ENABLE_PROFILER)
