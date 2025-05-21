#pragma once

#include <silk/engine/module/module_entry_points.h>
#include <silk/runtime/runtime_service.h>

namespace silk::runtime
{
    class RuntimeService;

    class RuntimeModuleEntryPoints : public ModuleEntryPoints
    {
    private:
        void Install(Engine& engine) override;
        void Uninstall(Engine& engine) override;

        RuntimeService m_RuntimeService;
    };
}
