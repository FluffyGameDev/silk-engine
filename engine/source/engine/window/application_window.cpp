#include <silk/engine/window/application_window.h>

#include <glfw/glfw3.h>

#include <silk/core/log.h>
#include <silk/core/log_categories.h>
#include <silk/engine/window/application_window_config.h>
#include <silk/engine/window/application_window_inputs.h>

namespace silk
{
    void ApplicationWindow::Init(ApplicationWindowConfig& config)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        m_Window = glfwCreateWindow(config.width, config.heigth, config.windowTitle, NULL, NULL);
        if (m_Window == NULL)
        {
            SILK_LOG_CRITICAL_ERROR(LogWindow, "Failed to create a window.");
            glfwTerminate();
        }

        glfwMakeContextCurrent(m_Window);

        glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);
    }

    void ApplicationWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;

        glfwTerminate();
    }

    void ApplicationWindow::SwapBuffer()
    {
        glfwSwapBuffers(m_Window);
    }

    void ApplicationWindow::PollInputs(ApplicationWindowInputs& inputs)
    {
        glfwPollEvents();
        if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(m_Window, true);
        }

        inputs.shouldCloseWindow |= (bool)glfwWindowShouldClose(m_Window);
    }
}
