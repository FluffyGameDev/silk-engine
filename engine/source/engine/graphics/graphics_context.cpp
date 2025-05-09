#include <silk/engine/graphics/graphics_context.h>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <silk/core/log.h>
#include <silk/core/log_categories.h>

namespace silk
{
    void GraphicsContext::Init()
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            SILK_LOG_CRITICAL_ERROR(LogWindow, "Failed to initialize GLAD.");
        }
    }

    void GraphicsContext::Shutdown()
    {
    }

    void GraphicsContext::Render()
    {
    }
}
