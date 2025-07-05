#include <silk/engine/graphics/shader.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <silk/core/log.h>
#include <silk/core/log_categories.h>

namespace silk
{
    namespace internal
    {
        static void CompileShader(GLuint shaderID, const char* shaderSource)
        {
            glShaderSource(shaderID, 1, &shaderSource, NULL);
            glCompileShader(shaderID);

            int infoLogLength{};
            GLint result{ GL_FALSE };
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
            if (infoLogLength > 0)
            {
                std::vector<char> errorMessage(static_cast<s64>(infoLogLength) + 1);
                glGetShaderInfoLog(shaderID, infoLogLength, NULL, &errorMessage[0]);
                SILK_LOG_ERROR(LogGraphics, "%s\n", &errorMessage[0]);
            }
        }

        static GLuint LinkShader(GLuint vertexShaderID, GLuint fragmentShaderID)
        {
            GLuint programID{ glCreateProgram() };
            glAttachShader(programID, vertexShaderID);
            glAttachShader(programID, fragmentShaderID);
            glLinkProgram(programID);

            int infoLogLength{};
            GLint result{ GL_FALSE };
            glGetProgramiv(programID, GL_LINK_STATUS, &result);
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
            if (infoLogLength > 0)
            {
                std::vector<char> errorMessage(static_cast<s64>(infoLogLength) + 1);
                glGetProgramInfoLog(programID, infoLogLength, NULL, &errorMessage[0]);
                SILK_LOG_ERROR(LogGraphics, "%s\n", &errorMessage[0]);
            }

            glDetachShader(programID, vertexShaderID);
            glDetachShader(programID, fragmentShaderID);

            return programID;
        }
    }

    void Shader::Create(const char* vertexSource, const char* fragmentSource)
    {
        GLuint vertexShaderID{ glCreateShader(GL_VERTEX_SHADER) };
        GLuint fragmentShaderID{ glCreateShader(GL_FRAGMENT_SHADER) };

        internal::CompileShader(vertexShaderID, vertexSource);
        internal::CompileShader(fragmentShaderID, fragmentSource);
        m_ShaderProgramId = internal::LinkShader(vertexShaderID, fragmentShaderID);

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    void Shader::Destroy()
    {
        glDeleteProgram(m_ShaderProgramId);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_ShaderProgramId);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    void Shader::SetUniform(const char* uniformName, s32 value)
    {
        GLuint uniformID = glGetUniformLocation(m_ShaderProgramId, uniformName);
        glUniform1i(uniformID, value);
    }

    void Shader::SetUniform(const char* uniformName, f32 value)
    {
        GLuint uniformID = glGetUniformLocation(m_ShaderProgramId, uniformName);
        glUniform1f(uniformID, value);
    }

    void Shader::SetUniform(const char* uniformName, const glm::vec2& vector)
    {
        GLuint uniformID = glGetUniformLocation(m_ShaderProgramId, uniformName);
        glUniform2f(uniformID, vector.x, vector.y);
    }

    void Shader::SetUniform(const char* uniformName, const glm::vec3& vector)
    {
        GLuint uniformID = glGetUniformLocation(m_ShaderProgramId, uniformName);
        glUniform3f(uniformID, vector.x, vector.y, vector.z);
    }

    void Shader::SetUniform(const char* uniformName, const glm::vec4& vector)
    {
        GLuint uniformID = glGetUniformLocation(m_ShaderProgramId, uniformName);
        glUniform4f(uniformID, vector.x, vector.y, vector.z, vector.w);
    }

    void Shader::SetUniform(const char* uniformName, const glm::mat4& matrix)
    {
        GLuint uniformID = glGetUniformLocation(m_ShaderProgramId, uniformName);
        glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}
