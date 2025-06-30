#pragma once

#include <vector>

#include <silk/core/types.h>

namespace silk
{
    class VertexBuffer
    {
    public:
        VertexBuffer(const void* vertexData, size_t vertexDataSize);
        VertexBuffer(VertexBuffer&& other);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

    private:
        u32 m_VertexBufferId;
    };
}
