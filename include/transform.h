#pragma once

#include "vec3.h"

struct transform_t {
  vec3f position;
  vec3f rotation;
  vec3f scale;

  // glm::mat4 matrix;
  // glm::mat4 inv_matrix;
};

void transform_update_matrices(struct transform_t *transform);
