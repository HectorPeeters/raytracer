#pragma once

#include "mat4.h"
#include "vec3.h"

struct transform_t {
  vec3f position;
  vec3f rotation;
  vec3f scale;

  mat4f matrix;
  mat4f inv_matrix;
};

void transform_update_matrices(struct transform_t *transform);
