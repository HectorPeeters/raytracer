#include "render_state.h"

#include "sphere.h"

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
  sphere sphere(transform(vec3f(0.0f, 0.0f, -2.0f), vec3f(0.0f, 0.0f, 0.0f),
                          vec3f(1.0f, 1.0f, 1.0f)));
  sphere.object_transform.update_matrices();

  // loop over each pixel in the scene
  for (int i = 0; i < buffer.width; i++) {
    for (int j = 0; j < buffer.height; j++) {
      // the final color of the pixel
      vec4f result(0.0f);

      // loop for each sample of this pixel
      for (int s = 0; s < settings.samples_per_pixel; s++) {
        f32 u = (i + (rand() / (f32)RAND_MAX)) / (f32)buffer.width;
        f32 v = (j + (rand() / (f32)RAND_MAX)) / (f32)buffer.height;

        ray_t camera_ray = render_camera.get_ray(u, v);

        bool hit = sphere.intersect(camera_ray);

        if (hit) {
          result += vec4f(0.0f, 0.0f, 1.0f, 1.0f);
        } else {
          vec3f dir = render_camera.get_ray(u, v).direction;
          f32 t = 0.5f * (dir.y + 1.0f);

          result += (1.0f - t) * vec4f(1.0f, 1.0f, 1.0f, 1.0f) +
                    t * vec4f(0.5f, 0.7f, 1.0f, 1.0f);
        }
      }

      // average all samples
      result /= settings.samples_per_pixel;

      // set the pixel value
      buffer.set(i, j, result);
    }
  }
}
