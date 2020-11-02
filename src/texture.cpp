#include "texture.h"

#include <glad/glad.h>

struct texture_data_t *texture_data_create(u16 width, u16 height,
                                           u8 components) {
  struct texture_data_t *result = ALLOC(texture_data_t);

  result->width = width;
  result->height = height;
  result->components = components;
  result->data = ALLOC_SIZED(u8, width * height * components);

  return result;
}

void texture_data_set(struct texture_data_t *texture, u16 x, u16 y, u8 r, u8 g,
                      u8 b) {
  ASSERT(texture->components == 3);

  u32 index = (x + y * texture->width) * texture->components;
  texture->data[index + 0] = r;
  texture->data[index + 1] = g;
  texture->data[index + 2] = b;
}
void texture_data_set(struct texture_data_t *texture, u16 x, u16 y, u8 r, u8 g,
                      u8 b, u8 a) {
  ASSERT(texture->components == 4);

  u32 index = (x + y * texture->width) * texture->components;
  texture->data[index + 0] = r;
  texture->data[index + 1] = g;
  texture->data[index + 2] = b;
  texture->data[index + 3] = a;
}

void texture_data_destroy(struct texture_data_t *texture) {
  FREE(texture->data);
  FREE(texture);
}

struct opengl_texture_t *texture_create(u16 width, u16 height, u8 components) {
  return texture_create(texture_data_create(width, height, components));
}

struct opengl_texture_t *texture_create(struct texture_data_t *data) {
  struct opengl_texture_t *texture = ALLOC(opengl_texture_t);

  glCreateTextures(GL_TEXTURE_2D, 1, &texture->id);

  texture->data = data;

  return texture;
}

void texture_update_data(struct opengl_texture_t *texture) {
  glBindTexture(GL_TEXTURE_2D, texture->id);

  u16 format;
  if (texture->data->components == 4) {
    format = GL_RGBA;
  } else {
    format = GL_RGB;
  }
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture->data->width,
                  texture->data->height, format, GL_UNSIGNED_BYTE,
                  texture->data->data);
}

void texture_destroy(struct opengl_texture_t *texture) {
  glDeleteTextures(1, &texture->id);
}
