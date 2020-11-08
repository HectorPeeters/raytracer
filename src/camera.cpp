#include "camera.h"

camera::camera(transform camera_transform, f32 fov, f32 near, f32 far,
               f32 aspect)
    : camera_transform(camera_transform), fov(fov), near(near), far(far),
      aspect_ratio(aspect) {
  horizontal = vec3f(2.0f  * aspect_ratio, 0.0f, 0.0f);
  vertical = vec3f(0.0f, 2.0f, 0.0f);
  lower_left =
      -horizontal / 2.0f - vertical / 2.0f - vec3f(0.0f, 0.0f, focal_length);
}

void camera::resize(u16 width, u16 height) {
  aspect_ratio = width / (f32)height;

  horizontal = vec3f(2.0f * aspect_ratio, 0.0f, 0.0f);
  vertical = vec3f(0.0f, 2.0f, 0.0f);
  lower_left =
      -horizontal / 2.0f - vertical / 2.0f - vec3f(0.0f, 0.0f, focal_length);
}

struct ray_t camera::get_ray(f32 u, f32 v) {
  return {
      vec3f(),
      (lower_left + horizontal * u + vertical * v).normalized(),
      F32_MAX,
  };
}
