#pragma once

#include <silk/core/types.h>

namespace silk
{
    class VertexBuffer
    {
    public:
        void Create(const void* vertexData, size_t vertexDataSize);
        void Destroy();

        void Bind() const;
        void Unbind() const;

    private:
        u32 m_VertexBufferId;
    };
}
