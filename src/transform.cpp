#include "transform.h"

void transform_update_matrices(struct transform_t *transform) {
  mat4f translated = mat4f::translation(transform->position);
  mat4f rotated = mat4f::rotation_euler(transform->rotation);
  mat4f scaled = mat4f::scale(transform->scale);
  transform->matrix = translated * rotated * scaled;
  transform->inv_matrix = transform->matrix.inverse();
}
