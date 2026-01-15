#include "lve/first_app.h"

int main(void) {
  LveFirstApp app;

  lve_first_app_create(&app);
  lve_first_app_run(&app);
}
