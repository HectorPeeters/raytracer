#pragma once

#include "texture.h"

struct render_settings_t {
  u16 width;
  u16 height;
  u32 samples_per_pixel;
};

struct render_state_t {
  struct texture_data_t *texture;
  struct render_settings_t settings;
};

struct render_settings_t render_settings_create(u16 width, u16 height,
                                                u32 samples_per_pixel);

struct render_state_t render_state_create(const char* scene_file);


void render_scene(struct render_state_t* state);
