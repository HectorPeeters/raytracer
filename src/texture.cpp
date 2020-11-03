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
  ASSERT((texture->components == 3));

  u32 index = (x + y * texture->width) * texture->components;
  texture->data[index + 0] = r;
  texture->data[index + 1] = g;
  texture->data[index + 2] = b;
}
void texture_data_set(struct texture_data_t *texture, u16 x, u16 y, u8 r, u8 g,
                      u8 b, u8 a) {
  ASSERT((texture->components == 4));

  u32 index = (x + y * texture->width) * texture->components;
  texture->data[index + 0] = r;
  texture->data[index + 1] = g;
  texture->data[index + 2] = b;
  texture->data[index + 3] = a;
}

void texture_data_clear(struct texture_data_t *texture, u16 r, u16 g, u16 b) {
  ASSERT((texture->components == 3));

  for (u32 i = 0; i < texture->width * texture->height; i++) {
    texture->data[i * texture->components + 0] = r;
    texture->data[i * texture->components + 0] = g;
    texture->data[i * texture->components + 0] = b;
  }
}

void texture_data_resize(struct texture_data_t *texture, u16 width, u16 height) {
  FREE(texture->data);
  texture->width = width;
  texture->height = height;
  texture->data = ALLOC_SIZED(u8, width * height * texture->components);
}

void texture_data_destroy(struct texture_data_t *texture) {
  FREE(texture->data);
  FREE(texture);
}

struct texture_t *texture_create(u16 width, u16 height, u8 components) {
  return texture_create(texture_data_create(width, height, components));
}

struct texture_t *texture_create(struct texture_data_t *data) {
  struct texture_t *texture = ALLOC(texture_t);

  glGenTextures(1, &texture->id);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  texture->data = data;

  u16 format;
  if (texture->data->components == 4) {
    format = GL_RGBA;
  } else {
    format = GL_RGB;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data->width, data->height, 0, format,
               GL_UNSIGNED_BYTE, data->data);

  LDEBG("Generated texture with id %d", texture->id);

  return texture;
}

void texture_update_data(struct texture_t *texture) {
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

void texture_destroy(struct texture_t *texture) {
  glDeleteTextures(1, &texture->id);
  texture_data_destroy(texture->data);
}
