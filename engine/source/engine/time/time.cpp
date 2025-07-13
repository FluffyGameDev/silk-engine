#include <silk/engine/time/time.h>

#include <chrono>

#include <silk/core/steady_clock.h>

namespace silk::time
{

    static std::chrono::time_point<SteadyClock> s_EngineStartTime{};

    void StartEngine()
    {
        s_EngineStartTime = SteadyClock::now();
    }

    float GetTime()
    {
        auto curTime = SteadyClock::now();
        std::chrono::duration<float> elapsedSeconds = curTime - s_EngineStartTime;
        return elapsedSeconds.count();
    }

}
