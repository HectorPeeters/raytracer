#include "ray.h"

static inline vec3f ray_at(struct ray_t *ray, float t) {
  ASSERT(APPROX_EQ(ray->direction.length_sqrt(), 1.0f));
  return ray->origin + ray->direction * t;
}
