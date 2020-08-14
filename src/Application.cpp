#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

#include "Shader.h"

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
    Shader* program = new Shader(SHADER_PATH);
    program->Bind(); // Binding once (outside render loop) as we are not gonna use other shaders for now.
    

    // Render loop.
    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render.
        glBindVertexArray(vao); // Bind vao.
        glDrawArrays(GL_TRIANGLES, 0, 3);   // Issue draw call.

        // Swap buffers and poll events.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up.
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    delete program;
    glfwTerminate();
    return 0;
}
