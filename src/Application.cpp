#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SHADER_PATH "res/shaders/source.shader"

// Defines a shader source object.
struct ShaderSource
{
    std::string vertexShader;
    std::string fragmentShader;
};

ShaderSource ParseShader(const std::string& filePath);
unsigned int CompileShader(unsigned int type, const std::string& source);

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(void)
{
    // Initialize GLFW library.
    if (!glfwInit())
        return 1;

    // Configure GLFW library.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window obejct.
    GLFWwindow* window = glfwCreateWindow(800, 600, "Titan", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 2;
    }
    glfwMakeContextCurrent(window);

    // Initialize glad before calling any opengl function.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return 3;
    }

    // Set viewport dimensions.
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    // Adjust viewport as the window resizes.
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

    glClearColor(0.1f, 0.f, 0.f, 1.f); // Screen will be cleared with a pink shade.

    // Vertex data
    float vertices[] = {
        // Positions        Color
        -.5f, -.5f, 0.f,    0.f, 1.f, 0.f,
         0.f,  .5f, 0.f,    0.f, 1.f, 0.f,
         .5f, -.5f, 0.f,    0.f, 0.f, 1.f,
    };

    // VAO.
    unsigned int vao;
    glGenVertexArrays(1, &vao);

    // VBO
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);     // tracked by vao.
    glBindVertexArray(0);
    glBufferData(GL_ARRAY_BUFFER, 3 * 6 * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (const void*)0);    // tracked by vao.
    glEnableVertexAttribArray(0);   // tracked by vao.
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (const void*)(3 * sizeof(float)));  // tracked by vao.
    glEnableVertexAttribArray(1);   // tracked by vao.
    glBindVertexArray(0);

    // Shader.
    ShaderSource shader = ParseShader(SHADER_PATH);
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, shader.vertexShader);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, shader.fragmentShader);
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    

    // Render loop.
    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render.
        glBindVertexArray(vao); // Bind vao.
        glUseProgram(program);  // Bind the shader.
        glDrawArrays(GL_TRIANGLES, 0, 3);   // Issue draw call.

        // Swap buffers and poll events.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up.
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(program);
    glfwTerminate();
    return 0;
}

ShaderSource ParseShader(const std::string& filePath)
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

unsigned int CompileShader(unsigned int type, const std::string& source)
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