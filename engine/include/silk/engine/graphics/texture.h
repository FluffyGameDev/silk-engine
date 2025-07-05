#pragma once

#include <silk/core/types.h>

namespace silk
{
    class Texture
    {
    public:
        Texture() = default;

        void Create(size_t width, size_t height, const void* pixelData);
        void Destroy();

        void Bind() const;
        void Unbind() const;

    private:
        u32 m_TextureId;
    };
}
