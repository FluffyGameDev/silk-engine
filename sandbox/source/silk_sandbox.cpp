#include <silk/engine/engine.h>
#include <silk/engine/engine_config.h>
#include <silk/runtime/runtime_module_entry_points.h>

int main()
{
    silk::EngineConfig engineConfig{ 30 };
    silk::Engine engine{ engineConfig };

    silk::runtime::RuntimeModuleEntryPoints runtimeModule{};
    engine.PreInstallModule(&runtimeModule);

    engine.Run();
}
