#pragma once

#include "math/mat4.h"
#include "math/vec3.h"

struct transform_t {
  vec3f position;
  vec3f rotation;
  vec3f scale;

  mat4f matrix;
  mat4f inv_matrix;
};

transform_t transform_default();

void transform_update_matrices(struct transform_t *transform);
