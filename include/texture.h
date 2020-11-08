#pragma once

#include "core.h"

#include "vec3.h"
#include "vec4.h"

template <typename T> class texture {
public:
  texture(u16 width, u16 height, u8 components)
      : width(width), height(height), components(components) {}

  texture(const texture &texture) = delete;

  texture(texture &&texture)
      : width(texture.width), height(texture.height),
        components(texture.components), data(texture.data) {}

  void init() { data = ALLOC_SIZED(T, width * height * components); }

  void destroy() { FREE(data); }

  void set(u16 x, u16 y, vec4<T> color) {
    u32 index = (x + y * width) * components;

    for (u8 i = 0; i < components; i++) {
      data[index + i] = color[i];
    }
  }

  void clear(vec4<T> color) {
    for (u32 i = 0; i < width * height; i++) {
      for (u8 j = 0; j < components; j++) {
        data[i * components + j] = color[j];
      }
    }
  }

  void resize(u16 new_width, u16 new_height) {
    FREE(data);

    width = new_width;
    height = new_height;

    data = ALLOC_SIZED(T, width * height * components);
  }

public:
  // the width of the texture
  u16 width;

  // the height of the texture
  u16 height;

  // the amount of components each pixel has: rgb -> 3, rgba -> 4
  u8 components;

  // the pixel data of the texture
  T *data;
};
