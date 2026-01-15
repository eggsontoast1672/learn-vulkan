#include "lve/first_app.h"

const int LVE_FIRST_APP_WIDTH = 800;
const int LVE_FIRST_APP_HEIGHT = 600;

void lve_first_app_create(LveFirstApp *app) {
  lve_window_create(&app->window, LVE_FIRST_APP_WIDTH, LVE_FIRST_APP_HEIGHT,
                    "Hello Vulkan!");
  lve_pipeline_create(&app->pipeline, "shaders/simple_shader.vert.spv",
                      "shaders/simple_shader.frag.spv");
}

void lve_first_app_destroy(const LveFirstApp *app) {
  lve_window_destroy(&app->window);
}

void lve_first_app_run(const LveFirstApp *app) {
  while (!lve_window_should_close(&app->window)) {
    glfwPollEvents();
  }
}
