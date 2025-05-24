#include "sandbox_debug_tool.h"

#include <imgui.h>

#include <silk/core/log.h>
#include "log_categories.h"

namespace silk::sandbox
{
    void SandboxDebugTool::OnRegister()
    {
        SILK_LOG_MESSAGE(LogSandbox, "SandboxDebugTool::OnRegister()");
    }

    void SandboxDebugTool::OnUnregister()
    {
        SILK_LOG_MESSAGE(LogSandbox, "SandboxDebugTool::OnUnregister()");
    }

    void SandboxDebugTool::Display()
    {
        if (ImGui::Begin("Sandbox"))
        {
            ImGui::Text("Some Text.");
        }
        ImGui::End();
    }
}
