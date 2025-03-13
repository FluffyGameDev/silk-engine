#include <silk/core/profiler.h>

#if defined(SILK_ENABLE_PROFILER)

#include <silk/core/log.h>
#include <silk/core/log_categories.h>

namespace silk
{
    Profiler Profiler::s_Instance{};

    void Profiler::LogProfileTiming(const char* timerName, s64 startTimeMicro, s64 endTimeMicro)
    {
        SILK_LOG_MESSAGE(LogCore, "%s(%ull ms)", timerName, endTimeMicro - startTimeMicro);
    }
}

#endif // defined(SILK_ENABLE_PROFILER)
