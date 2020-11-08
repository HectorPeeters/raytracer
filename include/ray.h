#pragma once

#include "math/vec3.h"
#include "core.h"

struct ray_t {
  vec3f origin;
  vec3f direction;

  f32 max_t;
};

static inline vec3f ray_at(struct ray_t *ray, float t);
