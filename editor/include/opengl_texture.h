#pragma once

#include <fstream>
#include <glad/glad.h>
#include <iostream>

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

template <typename T> inline u32 get_ppm_export_scale();
template <> inline u32 get_ppm_export_scale<f32>() { return 255; }
template <> inline u32 get_ppm_export_scale<u8>() { return 1; }

template <typename T> class opengl_texture {
public:
  opengl_texture() {}

  opengl_texture(const opengl_texture &texture) = delete;

  opengl_texture(opengl_texture &&texture)
      : id(texture.id), texture_data(texture_data) {}

  opengl_texture(texture<T> *texture) : texture_data(texture) {}

  void init() {
    texture_data->init();

    // generate the OpenGL texture
    glGenTextures(1, &id);
    // bind the OpenGL texture
    glBindTexture(GL_TEXTURE_2D, id);

    // set the filtering parameters of the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    u16 format = opengl_texture_format(texture_data->components);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_data->width,
                 texture_data->height, 0, format, get_opengl_type<T>(),
                 nullptr);

    LDEBG("Generated texture with id %d", id);
  }

  void destroy() {
    glDeleteTextures(1, &id);
    texture_data->destroy();
  }

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

    u16 format = opengl_texture_format(texture_data->components);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_data->width,
                 texture_data->height, 0, format, get_opengl_type<T>(),
                 nullptr);
  }

  void write_to_file(const char *path) {
    std::ofstream file;
    file.open(path);
    file << "P3\n";
    file << texture_data->width << " " << texture_data->height << "\n";
    file << "255\n";

    for (u16 y = 0; y < texture_data->height; y++) {
      for (u16 x = 0; x < texture_data->width; x++) {
        u32 index = (x + y * texture_data->width) * 4;

        vec4f pixel =
            vec4f(texture_data->data[index], texture_data->data[index + 1],
                  texture_data->data[index + 2], texture_data->data[index + 3]);
        pixel *= get_ppm_export_scale<T>();

        file << (u16)pixel.x << " " << (u16)pixel.y << " " << (u16)pixel.z
             << "\n";
      }
    }
  }

public:
  u32 id;
  texture<T> *texture_data;
};
