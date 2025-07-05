#pragma once

#include <glm/fwd.hpp>

#include <silk/core/types.h>

namespace silk
{
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

        void StartFrame();
        void EndFrame();

        void EnableScreenClear(const glm::vec3& color);
        void DisableScreenClear();
        void EnableDepthTest(DepthTestFunction depthTestFunction);
        void DisabletDepthTest();

        void DrawMesh(const Mesh& mesh) const;

    private:
        void RefreshClearFlags();

        u32 m_ClearFlags;
        bool m_IsClearEnabled;
        bool m_IsDepthTestEnabled;
    };
}
