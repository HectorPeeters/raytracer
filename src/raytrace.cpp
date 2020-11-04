#include "raytrace.h"

#include "serialize.h"

struct render_settings_t render_settings_create(u16 width, u16 height,
                                                u32 samples_per_pixel) {
  return render_settings_t{
      .width = width, .height = height, .samples_per_pixel = samples_per_pixel};
}

struct render_state_t render_state_create(const char *scene_file) {

  struct render_settings_t render_settings =
      deserialize_render_settings(read_json_file(scene_file));

  return render_state_t{texture_data_create(render_settings.width, render_settings.height, 3), render_settings};
}
