#pragma once

#include "ray.h"
#include "transform.h"
#include "intersection.h"

class intersectable {
public:
  intersectable(transform object_transform)
      : object_transform(object_transform) {}

  virtual bool intersect(const ray_t &ray, intersection& inter) = 0;
  virtual void init() {}
  virtual void destroy() {}

public:
  transform object_transform;
};
