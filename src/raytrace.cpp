#include "raytrace.h"

struct render_settings_t render_settings_create(u16 width, u16 height,
                                                u32 samples_per_pixel) {
  return render_settings_t{
      .width = width,
      .height = height,
      .samples_per_pixel = samples_per_pixel,
  };
}

