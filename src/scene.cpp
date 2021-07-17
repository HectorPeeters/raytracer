#include "scene.h"

scene::scene(transform object_transform) : intersectable(object_transform) {}

void scene::add_child(intersectable &object) { children.push_back(&object); }

bool scene::intersect(const ray_t &ray, intersection &inter) {
  f32 closest_hit = -1.0f;

  intersection temp_inter;

  for (auto object : children) {
    bool hit = object->intersect(ray, temp_inter);

    if (hit && temp_inter.t < closest_hit) {
      closest_hit = temp_inter.t;
      inter = temp_inter;
    }
  }

  return closest_hit > 0.0f;
}
