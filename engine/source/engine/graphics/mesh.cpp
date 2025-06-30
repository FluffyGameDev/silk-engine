#include <silk/engine/graphics/mesh.h>

#include <glad/glad.h>

namespace silk
{
    namespace internal
    {
        GLenum GetGLDataType(VertexDataType dataType)
        {
            switch (dataType)
            {
                case VertexDataType::Integer: return GL_INT;
                case VertexDataType::Float: return GL_FLOAT;
                case VertexDataType::Float2: return GL_FLOAT;
                case VertexDataType::Float3: return GL_FLOAT;
                case VertexDataType::Float4: return GL_FLOAT;
            }
            return GL_INVALID_ENUM;
        }

        u32 GetComponentCountDataType(VertexDataType dataType)
        {
            switch (dataType)
            {
                case VertexDataType::Integer: return 1;
                case VertexDataType::Float: return 1;
                case VertexDataType::Float2: return 2;
                case VertexDataType::Float3: return 3;
                case VertexDataType::Float4: return 4;
            }
            return GL_INVALID_ENUM;
        }

        GLsizei GetDataTypeSize(VertexDataType dataType)
        {
            switch (dataType)
            {
                case VertexDataType::Integer: return sizeof(u32);
                case VertexDataType::Float: return sizeof(float);
                case VertexDataType::Float2: return 2 * sizeof(float);
                case VertexDataType::Float3: return 3 * sizeof(float);
                case VertexDataType::Float4: return 4 * sizeof(float);
            }
            return 0;
        }
    }

    void Mesh::Create()
    {
        glGenVertexArrays(1, &m_VertexArrayId);
    }

    void Mesh::Destroy()
    {
        m_Buffers.clear();
        glDeleteVertexArrays(1, &m_VertexArrayId);
    }

    void Mesh::Bind() const
    {
        glBindVertexArray(m_VertexArrayId);
    }

    void Mesh::Unbind() const
    {
        glBindVertexArray(0);
    }

    void Mesh::AddVertexBuffer(const void* vertexData, size_t vertexDataSize, const VertexDataType* dataTypes, size_t dataTypeCount)
    {
        VertexBuffer& createdBuffer{ m_Buffers.emplace_back(vertexData, vertexDataSize) };
        createdBuffer.Bind();

        GLsizei stride{};
        for (size_t i = 0; i < dataTypeCount; ++i)
        {
            stride += internal::GetDataTypeSize(dataTypes[i]);
        }

        size_t offset{};
        for (size_t i = 0; i < dataTypeCount; ++i)
        {
            VertexDataType dataType{ dataTypes[i] };

            glEnableVertexAttribArray(m_VertexAttributionCount);

            u32 componentCount{ internal::GetComponentCountDataType(dataType) };
            GLenum glDataType{ internal::GetGLDataType(dataType) };
            glVertexAttribPointer(m_VertexAttributionCount, componentCount, glDataType, false, stride, (void*)offset);

            offset += internal::GetDataTypeSize(dataType);
            ++m_VertexAttributionCount;
        }

        createdBuffer.Unbind();
    }
}
