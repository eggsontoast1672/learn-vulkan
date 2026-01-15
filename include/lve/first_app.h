#pragma once

#include "lve/pipeline.h"
#include "lve/window.h"

extern const int LVE_FIRST_APP_WIDTH;
extern const int LVE_FIRST_APP_HEIGHT;

typedef struct {
  LveWindow window;
  LvePipeline pipeline;
} LveFirstApp;

void lve_first_app_create(LveFirstApp *app);
void lve_first_app_destroy(const LveFirstApp *app);
void lve_first_app_run(const LveFirstApp *app);
