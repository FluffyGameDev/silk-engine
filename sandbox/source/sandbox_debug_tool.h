#pragma once

#include <silk/engine/debug/debug_tool.h>

namespace silk::sandbox
{
    class SandboxDebugTool : public DebugTool
    {
    private:
        void OnRegister() override;
        void OnUnregister() override;

        void Display() override;
    };
}
