#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void resizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Get the primary monitor
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

    // Get the video mode of the primary monitor
    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

    // Choose the resolution of the monitor you want to display the window on
    int screenWidth = videoMode->width;
    int screenHeight = videoMode->height;

    // Create a window
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "My Window", primaryMonitor, NULL);

    // Make the window full screen
    glfwSetWindowMonitor(window, primaryMonitor, 0, 0, screenWidth, screenHeight, GLFW_DONT_CARE);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Render here

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
}
