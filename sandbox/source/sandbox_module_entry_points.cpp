#include "sandbox_module_entry_points.h"

#include <silk/engine/engine.h>

namespace silk::sandbox
{
    void SandboxModuleEntryPoints::Install(Engine& engine)
    {
        engine.GetDebugToolbox().RegisterTool(&m_SandboxDebugTool);
    }

    void SandboxModuleEntryPoints::Uninstall(Engine& engine)
    {
        engine.GetDebugToolbox().UnregisterTool(&m_SandboxDebugTool);
    }
}
