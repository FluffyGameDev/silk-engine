#include <silk/runtime/runtime_module_entry_points.h>

#include <silk/core/utility.h>
#include <silk/core/log.h>
#include <silk/runtime/log_categories.h>

namespace silk::runtime
{

    void RuntimeService::Init(Engine& engine)
    {
        SILK_UNUSED(engine);
        SILK_LOG_MESSAGE(LogRuntime, "RuntimeService::Init");
    }

    void RuntimeService::Shutdown(Engine& engine)
    {
        SILK_UNUSED(engine);
        SILK_LOG_MESSAGE(LogRuntime, "RuntimeService::Shutdown");
    }

}
