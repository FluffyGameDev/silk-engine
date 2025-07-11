#pragma once

#include <vector>

#include <glm/fwd.hpp>

#include <silk/core/types.h>

namespace silk
{
    class Camera;
    class Mesh;

    enum class DepthTestFunction : u8
    {
        Always,
        Never,
        Equal,
        NotEqual,
        Less,
        Greater,
        LessOrEqual,
        GreaterOrEqual
    };

    class GraphicsContext
    {
    public:
        GraphicsContext() = default;

        void Init();
        void Shutdown();

        void Render();

        void RegisterCamera(const Camera& camera);
        void UnregisterCamera(const Camera& camera);

        void EnableScreenClear(const glm::vec3& color);
        void DisableScreenClear();
        void EnableDepthTest(DepthTestFunction depthTestFunction);
        void DisableDepthTest();

        void DrawMesh(const Mesh& mesh) const;

    private:
        void RefreshClearFlags();

        std::vector<const Camera*> m_RegisteredCameras;
        u32 m_ClearFlags;
        bool m_IsClearEnabled;
        bool m_IsDepthTestEnabled;
    };
}
