#include "ray.h"

static inline glm::vec3 ray_at(struct ray_t *ray, float t) {
  ASSERT(APPROX_EQ(glm::length(ray->direction), 1.0f));
  return ray->origin + ray->direction * t;
}
