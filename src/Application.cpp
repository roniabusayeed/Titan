#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <cmath>

#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Renderer.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SHADER_PATH "res/shaders/source.shader"

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// Maximum number of vertex attributes supported on this hardware.
int MaxVertexAttributes()
{
    int maxAttribsCount;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttribsCount);
    return maxAttribsCount;
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
        // Positions            Color
        0.5f,   0.5f,  0.0f,      1.f, 1.f, 0.f,  //0
        0.5f,  -0.5f,  0.0f,      1.f, 0.f, 0.f,  //1
       -0.5f,  -0.5f,  0.0f,      1.f, .5f, 0.f,  //2
       -0.5f,   0.5f,  0.0f,      1.f, 0.f, 0.7f,  //3
    };

    // Indexed drawing.
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,
    };

    // Buffers.
    VertexBuffer vb = VertexBuffer(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    VertexArray vao =  VertexArray(vb, layout);
    IndexBuffer ibo =  IndexBuffer(indices, 6);

    // Shader.
    Shader program = Shader(SHADER_PATH);

    Renderer renderer;
    
    // Maximum vertex attributes suported on this machine's hardware.
    std::cout << "Max vertex attributes : " << MaxVertexAttributes() << std::endl;

    // Render loop.
    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);
        renderer.Clear();

        // Change color dynamically.
        float greenColor = .5f * sin(5 * glfwGetTime()) + .5f;   // vary between 0 to 1.
        program.Bind();
        program.SetUniform("u_color", greenColor);

        // Render.
        renderer.Draw(vao, ibo, program);

        // Swap buffers and poll events.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up.
    glfwTerminate();
    return 0;
}
