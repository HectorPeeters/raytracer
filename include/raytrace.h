#pragma once

#include "camera.h"
#include "texture.h"

struct render_settings_t {
  u16 width;
  u16 height;
  u32 samples_per_pixel;
};

struct render_state_t {
  texture<f32> buffer;
  struct render_settings_t settings;
  camera render_camera;
};

struct render_settings_t render_settings_create(u16 width, u16 height,
                                                u32 samples_per_pixel
                                                );

struct render_state_t render_state_create(struct render_settings_t settings, camera render_camera);

void render_scene(struct render_state_t *state);
