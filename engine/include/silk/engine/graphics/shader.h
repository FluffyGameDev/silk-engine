#pragma once

#include <glm/fwd.hpp>

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

        void SetUniform(const char* uniformName, s32 value);
        void SetUniform(const char* uniformName, f32 value);
        void SetUniform(const char* uniformName, const glm::vec2& vector);
        void SetUniform(const char* uniformName, const glm::vec3& vector);
        void SetUniform(const char* uniformName, const glm::vec4& vector);
        void SetUniform(const char* uniformName, const glm::mat4& matrix);

    private:
        u32 m_ShaderProgramId;
    };
}
