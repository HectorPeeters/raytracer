#include "render_state.h"

render_state::render_state(struct render_settings_t settings,
                           camera render_camera)
    : buffer(settings.width, settings.height, 4), settings(settings),
      render_camera(render_camera) {}

void render_state::init() { buffer.init(); }

void render_state::destroy() { buffer.destroy(); }

void render_state::resize(u16 width, u16 height) {
  buffer.resize(width, height);

  settings.width = width;
  settings.height = height;

  render_camera.resize(width, height);
}

void render_state::render_scene() {
  // loop over each pixel in the scene
  for (int i = 0; i < buffer.width; i++) {
    for (int j = 0; j < buffer.height; j++) {
      f32 u = i / (f32)buffer.width;
      f32 v = j / (f32)buffer.height;

      // the final color of the pixel
      vec4f result(0.0f);

      // loop for each sample of this pixel
      for (int s = 0; s < settings.samples_per_pixel; s++) {
        vec3f color = (render_camera.get_ray(u, v).direction + 1.0f) / 2.0f;
        result += vec4f(color.x, color.y, color.z, 1.0f);
      }

      // average all samples
      result /= settings.samples_per_pixel;

      // set the pixel value
      buffer.set(i, j, result);
    }
  }
}
