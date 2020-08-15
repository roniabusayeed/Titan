#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"

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

    // VBO
    VertexBuffer* vb = new VertexBuffer(vertices, sizeof(vertices));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);

    VertexArray* vao = new VertexArray(*vb, layout);
    vao->Bind();

    // Shader.
    Shader* program = new Shader(SHADER_PATH);
    program->Bind(); // Binding once (outside render loop) as we are not gonna use other shaders for now.
    

    // Render loop.
    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render.
        glDrawArrays(GL_TRIANGLES, 0, 3);   // Issue draw call.

        // Swap buffers and poll events.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up.
    delete vb;
    delete vao;
    delete program;
    glfwTerminate();
    return 0;
}
