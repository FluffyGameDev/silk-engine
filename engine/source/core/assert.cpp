#include <silk/core/assert.h>

#if defined(SILK_ENABLE_ASSERTS)

#include <cstdarg>
#include <cstdlib>

#include <silk/core/log.h>
#include <silk/core/log_categories.h>

namespace silk
{
    void Assert(bool condition, const char* message, ...)
    {
        if (!condition)
        {
#if defined(SILK_ENABLE_LOGS)
            static LogCategory assertLogCategory{ "ASSERTION" };
            va_list args{};
            va_start(args, message);
            LogVariadic(LogType::CriticalError, assertLogCategory, message, args);
            va_end(args);
#endif // defined(SILK_ENABLE_LOGS)

            std::abort();
        }
    }
}

#endif // defined(SILK_ENABLE_ASSERTS)
