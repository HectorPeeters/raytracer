#pragma once

#include "core.h"
#include "math/mat4.h"
#include "math/vec3.h"

struct ray_t {
  vec3f origin;
  vec3f direction;

  f32 max_t;
};

inline vec3f ray_at(struct ray_t *ray, float t);

ray_t ray_transform(const ray_t &ray, const mat4f &matrix);
