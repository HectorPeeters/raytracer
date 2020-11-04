#pragma once

#include <glm/glm.hpp>

struct transform_t {
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

  glm::mat4 matrix;
  glm::mat4 inv_matrix;
};

void transform_update_matrices(struct transform_t *transform);
