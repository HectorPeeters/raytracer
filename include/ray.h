#pragma once

#include <glm/glm.hpp>

#include "core.h"

struct ray_t {
  glm::vec3 origin;
  glm::vec3 direction;

  float max_t;
};

static inline glm::vec3 ray_at(struct ray_t *ray, float t);
