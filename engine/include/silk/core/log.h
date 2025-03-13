#pragma once

#if defined(SILK_ENABLE_LOGS)

namespace silk
{
    struct LogCategory;

    struct LogType
    {
        static const LogType Message;
        static const LogType Warning;
        static const LogType Error;
        static const LogType CriticalError;

        const char* const typeName;
        const void* const typeTarget;

    private:
        LogType(const char* name, void* target);
    };

    void Log(const LogType& logType, const LogCategory& logCategory, const char* message, ...);
    void LogVariadic(const LogType& logType, const LogCategory& logCategory, const char* message, void* args);

}

#define SILK_LOG_MESSAGE(logCategory, message, ...) silk::Log(silk::LogType::Message, logCategory, message, __VA_ARGS__)
#define SILK_LOG_WARNING(logCategory, message, ...) silk::Log(silk::LogType::Warning, logCategory, message, __VA_ARGS__)
#define SILK_LOG_ERROR(logCategory, message, ...) silk::Log(silk::LogType::Error, logCategory, message, __VA_ARGS__)
#define SILK_LOG_CRITICAL_ERROR(logCategory, message, ...) silk::Log(silk::LogType::CriticalError, logCategory, message, __VA_ARGS__)

#else

#define SILK_LOG_MESSAGE(logCategory, message, ...)
#define SILK_LOG_WARNING(logCategory, message, ...)
#define SILK_LOG_ERROR(logCategory, message, ...)
#define SILK_LOG_CRITICAL_ERROR(logCategory, message, ...)

#endif // defined(SILK_ENABLE_LOGS)
