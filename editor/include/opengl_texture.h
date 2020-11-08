#pragma once

#include <glad/glad.h>

#include "core.h"
#include "log.h"

static u16 opengl_texture_format(u8 components) {
  switch (components) {
  case 3:
    return GL_RGB;
  case 4:
    return GL_RGBA;
  default:
    LERR("Trying to get opengl texture format for %d components", components);
    return -1;
  }
}

template <typename T> inline u32 get_opengl_type();
template <> inline u32 get_opengl_type<f32>() { return GL_FLOAT; }
template <> inline u32 get_opengl_type<u8>() { return GL_UNSIGNED_BYTE; }

template <typename T> inline u32 get_ppm_export_scale();
template <> inline u32 get_ppm_export_scale<f32>() { return 255; }
template <> inline u32 get_ppm_export_scale<u8>() { return 1; }

template <typename T> class opengl_texture {
public:
  opengl_texture(u8 components, u16 width, u16 height)
      : components(components), width(width), height(height) {}

  opengl_texture(const opengl_texture &texture) = delete;

  opengl_texture(opengl_texture &&texture) : id(texture.id) {}

  void init() {
    // generate the OpenGL texture
    glGenTextures(1, &id);
    // bind the OpenGL texture
    glBindTexture(GL_TEXTURE_2D, id);

    // set the filtering parameters of the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    u16 format = opengl_texture_format(components);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format,
                 get_opengl_type<T>(), nullptr);

    LDEBG("Generated texture with id %d", id);
  }

  void destroy() { glDeleteTextures(1, &id); }

  void update_contents(void* data) {
    // bind the texture
    glBindTexture(GL_TEXTURE_2D, id);

    // determine the format based on the component count
    u16 format = opengl_texture_format(components);

    // update the contents of the texture
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, format,
                    get_opengl_type<T>(), data);
  }

  void resize(u16 new_width, u16 new_height) {
    if (width != new_width || height != new_height) {
      u16 format = opengl_texture_format(components);

      width = new_width;
      height = new_height;

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format,
                   get_opengl_type<T>(), nullptr);
    }
  }

public:
  u32 id;

  u8 components;

  u16 width;
  u16 height;
};
