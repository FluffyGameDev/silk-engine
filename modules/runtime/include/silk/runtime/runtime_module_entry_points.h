#pragma once

#include <silk/engine/module/module_entry_points.h>

namespace silk::runtime
{
    class RuntimeModuleEntryPoints : public ModuleEntryPoints
    {
        void Install(Engine& engine) override;
        void Uninstall(Engine& engine) override;
    };
}
