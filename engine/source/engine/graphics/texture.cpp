#include <silk/engine/graphics/texture.h>

#include <glad/glad.h>

namespace silk
{
    void Texture::Create(size_t width, size_t height, const void* pixelData)
    {
        glGenTextures(1, &m_TextureId);

        glBindTexture(GL_TEXTURE_2D, m_TextureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    void Texture::Destroy()
    {
        glDeleteTextures(1, &m_TextureId);
    }

    void Texture::Bind() const
    {
        glBindTexture(GL_TEXTURE_2D, m_TextureId);
    }

    void Texture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
