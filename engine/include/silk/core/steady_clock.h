#pragma once

namespace silk
{
    using SteadyClock = typename std::conditional<std::chrono::high_resolution_clock::is_steady,
        std::chrono::high_resolution_clock, std::chrono::steady_clock>::type;
}