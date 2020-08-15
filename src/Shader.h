#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>

struct ShaderSource
{
    std::string vertexShader;
    std::string fragmentShader;
};

class Shader
{
private:
    unsigned int m_id;
    mutable std::unordered_map<std::string, int> uniformLocationCache;
public:
    Shader(const std::string& shaderSourcePath);
    void Bind()const;
    void Unbind()const;
    void SetUniform(const std::string& uniformName, float value);
    ~Shader();
private:
    ShaderSource ParseShader(const std::string& filePath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    int GetUniformLocation(const std::string& uniformName)const;
};

#endif  // SHADER_H
