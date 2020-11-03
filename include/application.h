#pragma once

#include "core.h"
#include "window.h"
#include "raytrace.h"

struct application_t {
  bool running;
  struct window_t *window;

  struct render_state_t state;
  struct texture_t* texture;
};

struct application_t *application_create();

bool application_update(struct application_t *application);

void application_destroy(struct application_t *application);
