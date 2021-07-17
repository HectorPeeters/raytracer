#pragma once

#include <vector>

#include "intersectable.h"

class scene : public intersectable {
public:
  scene(transform object_transform);

  void add_child(intersectable &object);

  bool intersect(const ray_t &ray, intersection &inter);

private:
  std::vector<intersectable*> children;
};
