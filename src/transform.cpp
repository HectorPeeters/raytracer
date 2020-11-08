#include "transform.h"

transform::transform() {}
transform::transform(vec3f position) : position(position) {}
transform::transform(vec3f position, vec3f rotation, vec3f scale)
    : position(position), rotation(rotation), scale(scale) {}

void transform::update_matrices() {
  mat4f translated = mat4f::translation(position);
  mat4f rotated = mat4f::rotation_euler(rotation);
  mat4f scaled = mat4f::scale(scale);
  matrix = translated * rotated * scaled;
  inv_matrix = matrix.inverse();
}
