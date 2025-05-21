#include <silk/runtime/runtime_module_entry_points.h>

#include <silk/engine/engine.h>

namespace silk::runtime
{

    void RuntimeModuleEntryPoints::Install(Engine& engine)
    {
        engine.RegisterService(&m_RuntimeService);
    }

    void RuntimeModuleEntryPoints::Uninstall(Engine& engine)
    {
        engine.UnregisterService(&m_RuntimeService);
    }

}
