#include <silk/engine/debug/debug_toolbox.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

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

        static bool showDemoWindow{ true };
        if (showDemoWindow)
            ImGui::ShowDemoWindow(&showDemoWindow);
    }

    void DebugToolbox::EndFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
