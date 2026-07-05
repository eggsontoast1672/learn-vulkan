#include <cstring>
#include <iostream>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "lvk/device.hpp"
#include "lvk/instance.hpp"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
  HelloTriangleApplication()
      : m_physicalDevice(m_instance.getHandle()),
        m_logicalDevice(m_physicalDevice.getHandle()) {}

  void run() {
    initWindow();
    mainLoop();
    cleanup();
  }

private:
  GLFWwindow *m_window;

  lvk::Instance m_instance;
  lvk::PhysicalDevice m_physicalDevice;
  lvk::LogicalDevice m_logicalDevice;

  /// Initialize the window.
  void initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
  }

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
