#include "mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

void mesh::init() {
  tinyobj::attrib_t attributes;

  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  bool ret = tinyobj::LoadObj(&attributes, &shapes, &materials, nullptr,
                              nullptr, path);

  if (!ret) {
    LERR("Failed to load obj file %s", path);
  }

  for (u32 i = 0; i < attributes.vertices.size(); i += 3) {
    vertices.push_back(vec3f(attributes.vertices[i + 0],
                             attributes.vertices[i + 1],
                             attributes.vertices[i + 2]));
  }

  for (u32 i = 0; i < attributes.normals.size(); i += 3) {
    normals.push_back(vec3f(attributes.normals[i + 0],
                            attributes.normals[i + 1],
                            attributes.normals[i + 2]));
  }

  for (u32 i = 0; i < attributes.texcoords.size(); i += 2) {
    texture_coords.push_back(
        vec2f(attributes.normals[i + 0], attributes.normals[i + 1]));
  }

  for (u32 shape_index = 0; shape_index < shapes.size(); shape_index++) {
    u32 index_offset = 0;

    for (u32 face_index = 0;
         face_index < shapes[shape_index].mesh.num_face_vertices.size();
         face_index++) {

      u32 vertex_count = shapes[shape_index].mesh.num_face_vertices[face_index];

      for (u32 vertex_index = 0; vertex_index < vertex_count; vertex_index++) {
        tinyobj::index_t index =
            shapes[shape_index].mesh.indices[index_offset + vertex_index];

        triangles.push_back({(u32)(3 * index.vertex_index),
                             (u32)(3 * index.normal_index),
                             (u32)(2 * index.texcoord_index)});
      }

      index_offset += vertex_count;
    }
  }
}

void mesh::destroy() {}

static bool muller_trumbore(const ray_t &ray, const vec3f &v0, const vec3f &v1,
                            const vec3f &v2, f32 &t, vec3f &normal) {
  const vec3f edge1 = v1 - v0;
  const vec3f edge2 = v2 - v0;

  const vec3f h = ray.direction.cross(edge2);

  const f32 a = edge1.dot(h);

  if (a > -EPSILON && a < EPSILON) {
    return false;
  }

  const f32 f = 1.0f / a;
  const vec3f s = ray.origin - v0;
  const f32 u = f * s.dot(h);

  if (u < 0.0f || u > 1.0f) {
    return false;
  }

  vec3f q = s.cross(edge1);
  f32 v = f * ray.direction.dot(q);

  if (v < 0.0f || u + v > 1.0f) {
    return false;
  }

  const f32 temp_t = f * edge2.dot(q);
  if (temp_t < EPSILON) {
    return false;
  }

  normal = edge1.cross(edge2).normalized();

  t = temp_t;

  return true;
}

bool mesh::intersect(const ray_t &ray) {
  ray_t t_ray = ray_transform(ray, object_transform.inv_matrix);

  for (const struct index &idx : triangles) {
    const vec3f &v0 = vertices[idx.vertex_start_index];
    const vec3f &v1 = vertices[idx.vertex_start_index + 1];
    const vec3f &v2 = vertices[idx.vertex_start_index + 2];

    f32 t;
    vec3f normal;

    if (muller_trumbore(t_ray, v0, v1, v2, t, normal)) {
      return true;
    }

  }

  return false;
}
