#include "sphere.h"

bool sphere::intersect(const ray_t &ray) {
  ray_t t_ray = ray_transform(ray, object_transform.inv_matrix);

  f32 a = t_ray.direction.dot(t_ray.direction);
  f32 b = 2.0f * t_ray.origin.dot(t_ray.direction);
  f32 c = t_ray.origin.dot(t_ray.origin) - 1.0f;
  f32 disc = b * b - 4.0f * a * c;

  return disc > 0;
}
