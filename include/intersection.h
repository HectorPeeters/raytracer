#pragma once

#include "core.h"
#include "math/vec3.h"
#include "math/vec2.h"

struct intersection {
  f32 t;
  vec3f normal;
  vec2f uv;
};
