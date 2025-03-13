#pragma once

#if defined(SILK_ENABLE_ASSERTS)

namespace silk
{
    void Assert(bool condition, const char* message, ...);
}

#define SILK_ASSERT(condition, message, ...) silk::Assert(condition, message, __VA_ARGS__);

#else

#define SILK_ASSERT(condition, message, ...)

#endif // defined(SILK_ENABLE_ASSERTS)
