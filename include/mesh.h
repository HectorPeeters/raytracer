#pragma once

#include <vector>

#include "intersectable.h"
#include "math/vec2.h"
#include "math/vec3.h"

class mesh : public intersectable {
public:
  mesh(std::vector<vec3f> vertices, std::vector<vec3f> normals,
       std::vector<vec2f> texture_coords, std::vector<u32> indices,
       transform object_transform);

  mesh(const char *path, transform object_transform)
      : intersectable(object_transform), path(path) {}

  void init();

  void destroy();

  bool intersect(const ray_t &ray);

private:
  const char *path;

  std::vector<vec3f> vertices;
  std::vector<vec3f> normals;
  std::vector<vec2f> texture_coords;

  std::vector<u32> indices;
};
