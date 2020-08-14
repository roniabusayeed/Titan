#include "Shader.h"

#include <glad/glad.h>

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>

Shader::Shader(const std::string& shaderSourcePath)
{
    ShaderSource source = ParseShader(shaderSourcePath);

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, source.vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, source.fragmentShader);
    m_id = glCreateProgram();
    glAttachShader(m_id, vs);
    glAttachShader(m_id, fs);
    glLinkProgram(m_id);

    // Clean up intermediates.
    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Shader::Bind()const
{
    glUseProgram(m_id);
}

void Shader::Unbind()const
{
    glUseProgram(0);
}

Shader::~Shader()
{
    glDeleteProgram(m_id);
}

ShaderSource Shader::ParseShader(const std::string& filePath)
{
    enum class ShaderType
    {
        NONE = -1,
        VERTEX_SHADER = 0,
        FRAGMENT_SHADER = 1,
    };

    std::ifstream stream(filePath);
    if (!stream.is_open())
        assert(false);

    ShaderType type = ShaderType::NONE;
    std::stringstream ss[2];
    std::string line;
    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX_SHADER;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT_SHADER;

            continue;
        }

        if (type != ShaderType::NONE)
            ss[(int)type] << line << '\n';
    }

    stream.close();
    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // Handle shader compilation errors.
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* infoLog = new char[length];
        glGetShaderInfoLog(shader, length, nullptr, infoLog);

        std::string shaderType;
        if (type == GL_VERTEX_SHADER)
            shaderType = "Vertex";
        else if (type == GL_FRAGMENT_SHADER)
            shaderType = "Fragment";

        std::cout << "[" << shaderType << " Shader Compilation Error] " <<
            infoLog << std::endl;
        delete[] infoLog;

        assert(false);
        return 0;
    }

    return shader;
}
