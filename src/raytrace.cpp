#include "raytrace.h"

struct render_settings_t render_settings_create(u16 width, u16 height,
                                                u32 samples_per_pixel) {
  return render_settings_t{
      .width = width,
      .height = height,
      .samples_per_pixel = samples_per_pixel,
  };
}

struct render_state_t render_state_create(struct render_settings_t settings) {
  return render_state_t{
      texture<f32>(settings.width, settings.height, 4),
      settings,
  };
}

void render_scene(struct render_state_t *state) {
  // loop over each pixel in the scene
  for (int i = 0; i < state->buffer.width; i++) {
    for (int j = 0; j < state->buffer.height; j++) {

      // the final color of the pixel
      vec4f result(0.0f, 0.0f, 0.0f, 1.0f);

      // loop for each sample of this pixel
      for (int s = 0; s < state->settings.samples_per_pixel; s++)
        result += vec4f(rand(), rand(), rand(), 0.0f) / (f32)RAND_MAX;

      // average all samples
      result /= state->settings.samples_per_pixel;

      // set the pixel value
      state->buffer.set(i, j, result);
    }
  }
}
