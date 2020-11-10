#pragma once

#include <vector>

#include "intersectable.h"
#include "math/vec2.h"
#include "math/vec3.h"

struct index {
  u32 vertex_start_index;
  u32 normal_start_index;
  u32 texture_start_index;
};

class mesh : public intersectable {
public:
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

  std::vector<u32> vertex_indices;
};
