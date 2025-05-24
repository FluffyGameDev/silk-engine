#pragma once

#include <silk/engine/module/module_entry_points.h>

#include "sandbox_debug_tool.h"

namespace silk::sandbox
{
    class SandboxModuleEntryPoints : public ModuleEntryPoints
    {
    private:
        void Install(Engine& engine) override;
        void Uninstall(Engine& engine) override;

        SandboxDebugTool m_SandboxDebugTool;
    };
}
