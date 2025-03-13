#include <silk/core/profiling_scoped_timer.h>

#if defined(SILK_ENABLE_PROFILER)

#include <silk/core/profiler.h>

namespace silk
{
    ProfilingScopedTimer::ProfilingScopedTimer(const char* timerName)
        : m_TimerName{ timerName }
        , m_StartTime{ ProfilingClock::now() }
    {
    }

    ProfilingScopedTimer::~ProfilingScopedTimer()
    {
        s64 endTime{ std::chrono::duration_cast<std::chrono::microseconds>(ProfilingClock::now().time_since_epoch()).count() };
        s64 startTime{ std::chrono::duration_cast<std::chrono::microseconds>(m_StartTime.time_since_epoch()).count() };
        Profiler::get().LogProfileTiming(m_TimerName, startTime, endTime);
    }
}

#endif // defined(SILK_ENABLE_PROFILER)
