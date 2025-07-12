#include <silk/engine/graphics/camera.h>

#include <glm/gtc/matrix_transform.hpp>

#include <silk/engine/graphics/graphics_context.h>

namespace silk
{

    void Camera::ConfigurePerspective(float fov, float aspectRatio, float near, float far)
    {
        m_ProjectionMatrix = glm::perspective(fov, aspectRatio, near, far);
    }

    void Camera::ConfigureOrthographic(float left, float right, float bottom, float top)
    {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
        m_ViewMatrix = glm::mat4(1.0f);
    }

    void Camera::LookAt(const glm::vec3& from, const glm::vec3& to, const glm::vec3& up)
    {
        m_ViewMatrix = glm::lookAt(from, to, up);
    }



    void Camera::Draw(GraphicsContext& context) const
    {
        if (m_IsClearEnabled)
        {
            context.ClearScreen(m_ClearColor);
        }

        m_DrawSignal.Raise(context, *this);
    }



    void Camera::EnableScreenClear(const glm::vec3& color)
    {
        m_IsClearEnabled = true;
        m_ClearColor = color;
    }

    void Camera::DisableScreenClear()
    {
        m_IsClearEnabled = false;
    }
}
