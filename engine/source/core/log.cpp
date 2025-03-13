#include <silk/core/log.h>

#if defined(SILK_ENABLE_LOGS)

#include <cstdarg>
#include <cstdio>
#include <cstdlib>

#include <silk/core/log_categories.h>

namespace silk
{
    const LogType LogType::Message{ "MESSAGE", stdout };
    const LogType LogType::Warning{ "WARNING", stderr };
    const LogType LogType::Error{ "ERROR", stderr };
    const LogType LogType::CriticalError{ "CRITICAL", stderr };

    LogType::LogType(const char* name, void* target)
        : typeName{ name }
        , typeTarget{ target }
    {
    }

    void Log(const LogType& logType, const LogCategory& logCategory, const char* message, ...)
    {
        va_list args{};
        va_start(args, message);
        LogVariadic(logType, logCategory, message, args);
        va_end(args);
    }

    void LogVariadic(const LogType& logType, const LogCategory& logCategory, const char* message, void* args)
    {
        FILE* outputFile{ (FILE*)logType.typeTarget };

        fprintf_s(outputFile, "[%s][%s] ", logType.typeName, logCategory.categoryName);
        vfprintf(outputFile, message, (va_list)args);
        putc('\n', outputFile);
    }
}

#endif // defined(SILK_ENABLE_LOGS)
