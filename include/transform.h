#pragma once

#include "math/mat4.h"
#include "math/vec3.h"

class transform {
public:
  transform();
  transform(vec3f position);
  transform(vec3f position, vec3f rotation, vec3f scale);

  void update_matrices();

public:
  vec3f position{0.0f};
  vec3f rotation{0.0f};
  vec3f scale{1.0f};

  mat4f matrix;
  mat4f inv_matrix;
};
