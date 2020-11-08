#pragma once

#include "camera.h"
#include "texture.h"

struct render_settings_t {
  u16 width;
  u16 height;
  u32 samples_per_pixel;
};

struct render_settings_t render_settings_create(u16 width, u16 height,
                                                u32 samples_per_pixel);
