#pragma once

#include "core.h"
#include "ray.h"
#include "transform.h"

class camera {
public:
  camera(struct transform_t transform, f32 fov, f32 near, f32 far, f32 aspect);

  struct ray_t get_ray(f32 u, f32 v);

private:
  struct transform_t transform;
  f32 fov;

  f32 near;
  f32 far;

  f32 aspect_ratio;

  f32 focal_length;

  vec3f horizontal;
  vec3f vertical;
  vec3f lower_left;
};
