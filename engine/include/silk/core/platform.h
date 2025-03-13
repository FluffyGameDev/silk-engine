#pragma once

#if defined(_WIN32)
    #define SILK_PLATFORM_WINDOWS 1
#else
    #error Unknown Platform.
#endif
