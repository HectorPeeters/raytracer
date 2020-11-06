#include "opengl_texture.h"

#include <glad/glad.h>

struct texture_t *texture_create(u16 width, u16 height, u8 components) {
  // create a new texture using a newly constructed texture data struct
  return texture_create(texture_data_create(width, height, components));
}

u16 get_opengl_texture_format(u8 components) {
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

struct texture_t *texture_create(struct texture_data_t *data) {
  // allocate data for the struct
  struct texture_t *texture = ALLOC(texture_t);

  // generate the OpenGL texture
  glGenTextures(1, &texture->id);
  // bind the OpenGL texture
  glBindTexture(GL_TEXTURE_2D, texture->id);

  // set the filtering parameters of the texture
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  // assign the texture data to the struct
  texture->data = data;

  // determine the format based on the component count
  u16 format = get_opengl_texture_format(texture->data->components);

  // load the initial pixel values to the texture. this will be all zero but
  // this way OpenGL knows how big our texture is which allows us to use
  // SubImage2D later on
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data->width, data->height, 0, format,
               GL_UNSIGNED_BYTE, data->data);

  LDEBG("Generated texture with id %d", texture->id);

  return texture;
}

void texture_resize(struct texture_t *texture, u16 width, u16 height) {
  texture_data_resize(texture->data, width, height);

  glBindTexture(GL_TEXTURE_2D, texture->id);

  // determine the format based on the component count
  u16 format = get_opengl_texture_format(texture->data->components);

  // load the initial pixel values to the texture. this will be all zero but
  // this way OpenGL knows how big our texture is which allows us to use
  // SubImage2D later on
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->data->width, texture->data->height, 0, format,
               GL_UNSIGNED_BYTE, texture->data->data);
}

void texture_update_data(struct texture_t *texture) {
  // bind the texture
  glBindTexture(GL_TEXTURE_2D, texture->id);

  // determine the format based on the component count
  u16 format = get_opengl_texture_format(texture->data->components);

  // update the contents of the texture
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture->data->width,
                  texture->data->height, format, GL_UNSIGNED_BYTE,
                  texture->data->data);
}

void texture_destroy(struct texture_t *texture) {
  // delete the opengl texture
  glDeleteTextures(1, &texture->id);

  // delete the data struct
  texture_data_destroy(texture->data);

  // delete the actual struct
  FREE(texture);
}
