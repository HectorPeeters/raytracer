#pragma once

#include "camera.h"
#include "texture.h"

struct render_settings_t {
  u16 width{1920};
  u16 height{1080};
  u32 samples_per_pixel{20};
  u8 thread_count{16};
};
