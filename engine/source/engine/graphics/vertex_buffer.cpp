#include <silk/engine/graphics/vertex_buffer.h>

#include <glad/glad.h>

namespace silk
{
    VertexBuffer::VertexBuffer(const void* vertexData, size_t vertexDataSize)
    {
        glGenBuffers(1, &m_VertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_VertexBufferId);
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
