#include <silk/engine/graphics/graphics_context.h>

#include <algorithm>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <silk/core/log.h>
#include <silk/core/log_categories.h>
#include <silk/engine/graphics/camera.h>
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

        m_ClearFlags = 0;
        m_IsClearEnabled = false;
        m_IsDepthTestEnabled = false;
    }

    void GraphicsContext::Shutdown()
    {
    }



    void GraphicsContext::Render()
    {
        if (m_IsClearEnabled)
        {
            glClear(m_ClearFlags);
        }

        //TODO: order cameras by priority only when needed
        std::sort(m_RegisteredCameras.begin(), m_RegisteredCameras.end(),
            [](const Camera* lhs, const Camera* rhs) { return lhs->GetPriority() > rhs->GetPriority(); });

        for (const Camera* camera : m_RegisteredCameras)
        {
            camera->Draw(*this);
        }
    }



    void GraphicsContext::RegisterCamera(const Camera& camera)
    {
        m_RegisteredCameras.push_back(&camera);
    }

    void GraphicsContext::UnregisterCamera(const Camera& camera)
    {
        auto endIt{ m_RegisteredCameras.end() };
        auto remIt{ std::remove(m_RegisteredCameras.begin(), endIt, &camera) };
        if (remIt != endIt)
        {
            m_RegisteredCameras.erase(remIt, endIt);
        }
    }



    void GraphicsContext::EnableScreenClear(const glm::vec3& color)
    {
        m_IsClearEnabled = true;
        glClearColor(color.x, color.y, color.z, 1.0f);

        RefreshClearFlags();
    }

    void GraphicsContext::DisableScreenClear()
    {
        m_IsClearEnabled = false;

        RefreshClearFlags();
    }

    void GraphicsContext::EnableDepthTest(DepthTestFunction depthTestFunction)
    {
        m_IsDepthTestEnabled = true;
        glEnable(GL_DEPTH_TEST);

        GLenum functionValue{};
        switch (depthTestFunction)
        {
            case DepthTestFunction::Always: { functionValue = GL_ALWAYS; break; }
            case DepthTestFunction::Never: { functionValue = GL_NEVER; break; }
            case DepthTestFunction::Equal: { functionValue = GL_EQUAL; break; }
            case DepthTestFunction::NotEqual: { functionValue = GL_NOTEQUAL; break; }
            case DepthTestFunction::Less: { functionValue = GL_LESS; break; }
            case DepthTestFunction::Greater: { functionValue = GL_GREATER; break; }
            case DepthTestFunction::LessOrEqual: { functionValue = GL_LEQUAL; break; }
            case DepthTestFunction::GreaterOrEqual: { functionValue = GL_GEQUAL; break; }
            default:
            {
                functionValue = GL_LESS;
                SILK_LOG_ERROR(LogGraphics, "Incorrect depth test function (got: %d)", (u8)depthTestFunction);
            }
        }
        glDepthFunc(GL_LESS);

        RefreshClearFlags();
    }

    void GraphicsContext::DisableDepthTest()
    {
        m_IsDepthTestEnabled = false;
        glDisable(GL_DEPTH_TEST);

        RefreshClearFlags();
    }

    void GraphicsContext::RefreshClearFlags()
    {
        m_ClearFlags = 0;
        if (m_IsClearEnabled) { m_ClearFlags |= GL_COLOR_BUFFER_BIT; }
        if (m_IsDepthTestEnabled) { m_ClearFlags |= GL_DEPTH_BUFFER_BIT; }
    }



    void GraphicsContext::DrawMesh(const Mesh& mesh) const
    {
        mesh.Bind();
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mesh.GetVertexCount());
        mesh.Unbind();
    }
}
