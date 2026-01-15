#include <stdio.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cglm/struct.h>

int main(void) {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  GLFWwindow *window = glfwCreateWindow(800, 600, "Vulkan window", NULL, NULL);
  uint32_t extension_count;

  vkEnumerateInstanceExtensionProperties(NULL, &extension_count, NULL);
  printf("%d extensions supported\n", extension_count);

  mat4s matrix = glms_mat4_identity();
  vec4s vec = glms_vec4_zero();
  vec4s test = glms_mat4_mulv(matrix, vec);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
