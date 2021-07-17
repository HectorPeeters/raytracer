#pragma once

#include "intersectable.h"

class sphere : public intersectable {
public:
  sphere(transform object_transform) : intersectable(object_transform) {}

  bool intersect(const ray_t& ray, intersection& inter);
};
