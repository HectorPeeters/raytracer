#pragma once

#include "core.h"
#include "texture.h"
#include "window.h"

struct application_t {
  bool running;
  struct window_t *window;

  struct opengl_texture_t *texture;
};

struct application_t *application_create();

bool application_update(struct application_t *application);

void application_destroy(struct application_t *application);
