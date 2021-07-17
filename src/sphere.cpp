#include "sphere.h"

bool sphere::intersect(const ray_t &ray, intersection &inter) {
  ray_t t_ray = ray_transform(ray, object_transform.inv_matrix);

  f32 a = t_ray.direction.dot(t_ray.direction);
  f32 b = 2.0f * t_ray.origin.dot(t_ray.direction);
  f32 c = t_ray.origin.dot(t_ray.origin) - 1.0f;
  f32 disc = b * b - 4.0f * a * c;

  if (disc < 0.0f) {
    return false;
  }

  if (disc == 0.0f) {
    inter.t = -b / (2.0f * a);
    return true;
  }

  inter.t = (-b - sqrtf(disc)) / (2.0f * a);

  return true;
}
