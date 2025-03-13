#pragma once

#if defined(SILK_ENABLE_PROFILER)

#include <silk/core/types.h>

namespace silk
{
    class Profiler
    {
    public:
        inline static Profiler& get();

        void LogProfileTiming(const char* timerName, s64 startTimeMicro, s64 endTimeMicro);

    private:
        Profiler() = default;

        static Profiler s_Instance;
    };

    inline Profiler& Profiler::get()
    {
        return s_Instance;
    }
}

#endif // defined(SILK_ENABLE_PROFILER)
