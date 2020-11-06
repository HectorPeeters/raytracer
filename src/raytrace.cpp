#include "raytrace.h"

#include <glm/glm.hpp>

struct render_settings_t render_settings_create(u16 width, u16 height,
                                                u32 samples_per_pixel) {
  return render_settings_t{
      .width = width, .height = height, .samples_per_pixel = samples_per_pixel};
}

struct render_state_t render_state_create(struct render_settings_t settings) {
  return render_state_t{texture_data_create(settings.width, settings.height, 3),
                        settings};
}

void render_scene(struct render_state_t *state) {
  // loop over each pixel in the scene
  for (int i = 0; i < state->texture->width; i++) {
    for (int j = 0; j < state->texture->height; j++) {

      // the final color of the pixel
      glm::vec3 result{0.0};

      // loop for each sample of this pixel
      for (int s = 0; s < state->settings.samples_per_pixel; s++)
        result += glm::vec3{rand() % 255, rand() % 255, rand() % 255};

      // average all samples
      result /= state->settings.samples_per_pixel;

      // set the pixel value
      texture_data_set(state->texture, i, j, result.x, result.y, result.z);
    }
  }
}
