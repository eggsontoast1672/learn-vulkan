#include "lvk/instance.hpp"
#include <cstring>
#include <format>
#include <iostream>
#include <stdexcept>
#include <vector>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
  void run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
  }

private:
  GLFWwindow *m_window;

  lvk::Instance m_instance;

  /// Initialize the window.
  void initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
  }

  void initVulkan() {}

  /// Start the main loop.
  void mainLoop() {
    while (!glfwWindowShouldClose(m_window)) {
      glfwPollEvents();
    }
  }

  void cleanup() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
  }
};

int main() {
  HelloTriangleApplication app;

  try {
    app.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
