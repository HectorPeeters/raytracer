#pragma once

#include "core.h"
#include "ray.h"
#include "transform.h"

class camera {
public:
  camera(transform camera_transform, f32 fov, f32 near, f32 far, f32 aspect);

  void resize(u16 width, u16 height);

  struct ray_t get_ray(f32 u, f32 v);

private:
  transform camera_transform;
  f32 fov;

  f32 near;
  f32 far;

  f32 aspect_ratio;

  f32 focal_length{1.0f};

  vec3f horizontal;
  vec3f vertical;
  vec3f lower_left;
};
