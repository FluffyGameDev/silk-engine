#pragma once

#include <vector>

#include <silk/core/types.h>
#include <silk/engine/graphics/vertex_buffer.h>

namespace silk
{
    enum class VertexDataType
    {
        Integer,
        Float,
        Float2,
        Float3,
        Float4
    };

    class Mesh
    {
    public:
        Mesh() = default;

        void Create();
        void Destroy();

        void Bind() const;
        void Unbind() const;

        u32 GetVertexCount() const { return m_VertexCount; }

        void AddVertexBuffer(const void* vertexData, size_t vertexDataSize, const VertexDataType* dataTypes, size_t dataTypeCount);

    private:
        std::vector<VertexBuffer> m_Buffers;
        u32 m_VertexArrayId;
        u32 m_VertexAttributionCount;
        u32 m_VertexCount;
    };
}
