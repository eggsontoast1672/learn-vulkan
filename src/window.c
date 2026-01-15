#include "lve/window.h"

static void init_window(LveWindow *window) {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window->window = glfwCreateWindow(window->width, window->height,
                                    window->window_name, NULL, NULL);
}

void lve_window_create(LveWindow *window, int width, int height,
                       const char *name) {
  window->width = width;
  window->height = height;
  window->window_name = name;

  init_window(window);
}

void lve_window_destroy(const LveWindow *window) {
  glfwDestroyWindow(window->window);
  glfwTerminate();
}

bool lve_window_should_close(const LveWindow *window) {
  return glfwWindowShouldClose(window->window);
}
