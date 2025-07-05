#include <silk/engine/graphics/graphics_context.h>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <silk/core/log.h>
#include <silk/core/log_categories.h>
#include <silk/engine/graphics/mesh.h>

namespace silk
{
#ifdef SILK_GRAPHICS_DEBUGGING
    void GLAPIENTRY onGlDebugMessage(GLenum, GLenum type, GLuint, GLenum severity, GLsizei, const GLchar* message, const void*)
    {
        if (type == GL_DEBUG_TYPE_ERROR)
        {
            const char* severityText = "UNKNOWN";
            switch (severity)
            {
                case GL_DEBUG_SEVERITY_LOW: { severityText = "LOW SEVERITY"; break; }
                case GL_DEBUG_SEVERITY_MEDIUM: { severityText = "MEDIUM SEVERITY"; break; }
                case GL_DEBUG_SEVERITY_HIGH: { severityText = "HIGH SEVERITY"; break; }
                case GL_DEBUG_SEVERITY_NOTIFICATION: { severityText = "NOTIFICATION"; break; }
            }

            SILK_LOG_ERROR(LogGraphics, "[%s] %s", severityText, message);
        }
    }
#endif //SILK_GRAPHICS_DEBUGGING


    void GraphicsContext::Init()
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            SILK_LOG_CRITICAL_ERROR(LogGraphics, "Failed to initialize GLAD.");
        }

#ifdef SILK_GRAPHICS_DEBUGGING
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(onGlDebugMessage, 0);
#endif //SILK_GRAPHICS_DEBUGGING
    }

    void GraphicsContext::Shutdown()
    {
    }

    void GraphicsContext::StartFrame()
    {
        glClearColor(0.0f, 0.0f, 0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GraphicsContext::EndFrame()
    {
    }

    void GraphicsContext::DrawMesh(const Mesh& mesh) const
    {
        mesh.Bind();
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mesh.GetVertexCount());
        mesh.Unbind();
    }
}
