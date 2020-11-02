#include "window.h"

int main() {
  struct window_t *window = window_create(1920 / 2, 1080 / 2, "Raytracer");

  while (!window_should_close(window)) {
    window_input();

    window_update(window);
  }

  window_destroy(window);

  return 0;
}
