#include "ray.h"

inline vec3f ray_at(struct ray_t *ray, float t) {
  ASSERT(APPROX_EQ(ray->direction.length_sqrt(), 1.0f));
  return ray->origin + ray->direction * t;
}

ray_t ray_transform(const ray_t &ray, const mat4f &matrix) {
  vec4f transformed_pos =
      matrix * vec4f(ray.origin.x, ray.origin.y, ray.origin.z, 1.0f);
  vec4f transformed_dir =
      matrix * vec4f(ray.direction.x, ray.direction.y, ray.direction.z, 0.0f);

  return ray_t{
      vec3f(transformed_pos.x, transformed_pos.y, transformed_pos.z),
      vec3f(transformed_dir.x, transformed_dir.y, transformed_dir.z),
  };
}
