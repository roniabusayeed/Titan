#ifndef SHADER_H
#define SHADER_H

#include <string>

struct ShaderSource
{
    std::string vertexShader;
    std::string fragmentShader;
};

class Shader
{
private:
    unsigned int m_id;
public:
    Shader(const std::string& shaderSourcePath);
    void Bind()const;
    void Unbind()const;
    ~Shader();
private:
    ShaderSource ParseShader(const std::string& filePath);
    unsigned int CompileShader(unsigned int type, const std::string& source);

};

#endif  // SHADER_H
