#pragma once

#include <glm/glm.hpp>

#include <silk/core/signal.h>
#include <silk/core/types.h>

namespace silk
{
    class GraphicsContext;

    class Camera
    {
    public:
        void ConfigurePerspective(float fov, float aspectRatio, float near, float far);
        void ConfigureOrthographic(float left, float right, float bottom, float top);
        void LookAt(const glm::vec3& from, const glm::vec3& to, const glm::vec3& up);

        void Draw(GraphicsContext& context) const;

        void EnableScreenClear(const glm::vec3& color);
        void DisableScreenClear();

        inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        inline Signal<void(GraphicsContext&, const Camera&)>& GetDrawSignal() { return m_DrawSignal; }
        inline u32 GetPriority() const { return m_Priority; }
        inline void SetPriority(u32 priority) { m_Priority = priority; }

    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::vec3 m_ClearColor;
        Signal<void(GraphicsContext&, const Camera&)> m_DrawSignal;
        u32 m_Priority;
        bool m_IsClearEnabled;
    };
}
