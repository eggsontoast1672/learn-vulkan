#pragma once

#include <stdbool.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

typedef struct {
  int width;
  int height;
  const char *window_name;
  GLFWwindow *window;
} LveWindow;

void lve_window_create(LveWindow *window, int width, int height, const char *name);
void lve_window_destroy(const LveWindow *window);
bool lve_window_should_close(const LveWindow *window);
