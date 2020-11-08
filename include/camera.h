#pragma once

#include "core.h"
#include "transfom.h"

struct camera_t {
  struct transform_t transform;
  f32 fov;
  f32 near;
  f32 far;
};
