#pragma once

#if defined(SILK_ENABLE_LOGS)

namespace silk
{
    struct LogCategory
    {
        const char* const categoryName;
    };
}

#define SILK_DEFINE_LOG_CATEGORY(categoryVariable, categoryName) inline static const silk::LogCategory categoryVariable{ categoryName }

#else

#define SILK_DEFINE_LOG_CATEGORY(categoryVariable, categoryName)

#endif // defined(SILK_ENABLE_LOGS)

namespace silk
{
    SILK_DEFINE_LOG_CATEGORY(LogCore, "CORE");
    SILK_DEFINE_LOG_CATEGORY(LogGraphics, "GRAPHICS");
    SILK_DEFINE_LOG_CATEGORY(LogInput, "INPUT");
    SILK_DEFINE_LOG_CATEGORY(LogWindow, "WINDOW");
}
