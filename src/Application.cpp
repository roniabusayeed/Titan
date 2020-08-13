#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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


    // Render loop.
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers and poll events.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up.
    glfwTerminate();
    return 0;
}