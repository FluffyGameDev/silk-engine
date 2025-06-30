#include <silk/engine/graphics/shader.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glad/glad.h>

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
}
