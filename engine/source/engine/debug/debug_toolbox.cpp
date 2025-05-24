#include <silk/engine/debug/debug_toolbox.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <silk/engine/debug/debug_tool.h>
#include <silk/engine/window/application_window.h>

namespace silk
{
    void DebugToolbox::Init(ApplicationWindow& applicationWindow)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(applicationWindow.GetWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    void DebugToolbox::Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void DebugToolbox::StartFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        for (DebugTool* tool : m_DebugTools)
        {
            tool->Display();
        }
    }

    void DebugToolbox::EndFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void DebugToolbox::RegisterTool(DebugTool* tool)
    {
        m_DebugTools.push_back(tool);
        tool->OnRegister();
    }

    void DebugToolbox::UnregisterTool(DebugTool* tool)
    {
        tool->OnUnregister();
        auto endIt{ m_DebugTools.end() };
        auto removeIt{ std::remove(m_DebugTools.begin(), endIt, tool) };
        if (removeIt != endIt)
        {
            m_DebugTools.erase(removeIt, endIt);
        }
    }
}
