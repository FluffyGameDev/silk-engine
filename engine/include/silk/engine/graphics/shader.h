#pragma once

#include <silk/core/types.h>

namespace silk
{
    class Shader
    {
    public:
        void Create(const char* vertexSource, const char* fragmentSource);
        void Destroy();

        void Bind() const;
        void Unbind() const;

    private:
        u32 m_ShaderProgramId;
    };
}
