#include <silk/engine/engine.h>

#include <chrono>
#include <thread>

#include <silk/core/steady_clock.h>
#include <silk/engine/engine_config.h>

namespace silk
{
    void RunEngine(const EngineConfig& config)
    {
        std::chrono::microseconds targetFrameLength{ 1000000LL / static_cast<typename std::chrono::microseconds::rep>(config.targetFps) };

        bool keepRunning{ true };
        while (keepRunning)
        {
            auto frameStartTime = SteadyClock::now();

            //Poll Inputs
            //Update
            //Render

            auto frameDuration{ std::chrono::duration_cast<decltype(targetFrameLength)>(SteadyClock::now() - frameStartTime)};
            if (frameDuration < targetFrameLength)
            {
                std::this_thread::sleep_for(targetFrameLength - frameDuration);
            }
        }
    }
}
