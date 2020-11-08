#pragma once

#include <glad/glad.h>

#include "core.h"
#include "log.h"
#include "texture.h"

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

// TODO: fix the taking in of a pointer to the texture
template <typename T> class opengl_texture {
public:
  opengl_texture() {}

  opengl_texture(const opengl_texture &texture) = delete;

  opengl_texture(opengl_texture &&texture)
      : id(texture.id), texture_data(texture_data) {}

  opengl_texture(texture<T> *texture) : texture_data(texture) {
    // generate the OpenGL texture
    glGenTextures(1, &id);
    // bind the OpenGL texture
    glBindTexture(GL_TEXTURE_2D, id);

    // set the filtering parameters of the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    u16 format = opengl_texture_format(texture_data->components);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_data->width,
                 texture_data->height, 0, format, get_opengl_type<T>(), nullptr);

    LDEBG("Generated texture with id %d", id);
  }

  ~opengl_texture() { glDeleteTextures(1, &id); }

  void update_contents() {
    // bind the texture
    glBindTexture(GL_TEXTURE_2D, id);

    // determine the format based on the component count
    u16 format = opengl_texture_format(texture_data->components);

    // update the contents of the texture
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture_data->width,
                    texture_data->height, format, get_opengl_type<T>(),
                    texture_data->data);
  }

  void set(u16 x, u16 y, vec4<T> color) { texture_data->set(x, y, color); }

  void clear(vec4<T> color) { texture_data->clear(color); }

  void resize(u16 new_width, u16 new_height) {
    texture_data->resize(new_width, new_height);
  }

public:
  u32 id;
  texture<T> *texture_data;
};
