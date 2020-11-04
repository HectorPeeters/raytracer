#include "texture.h"

#include <glad/glad.h>

struct texture_data_t *texture_data_create(u16 width, u16 height,
                                           u8 components) {
  // allocate data for the texture data struct
  struct texture_data_t *result = ALLOC(texture_data_t);

  // set the width and height of the texture
  result->width = width;
  result->height = height;

  // set the component count
  result->components = components;

  // allocate data for the pixels
  result->data = ALLOC_SIZED(u8, width * height * components);

  return result;
}

void texture_data_set(struct texture_data_t *texture, u16 x, u16 y, u8 r, u8 g,
                      u8 b) {
  // check if the component count is 3 since we are setting RGB values
  ASSERT((texture->components == 3));

  // calculate the index of the pixel
  u32 index = (x + y * texture->width) * texture->components;

  // set each channel of the pixel
  // TODO: possible optimization: combine all pixels into one value and set then
  texture->data[index + 0] = r;
  texture->data[index + 1] = g;
  texture->data[index + 2] = b;
}
void texture_data_set(struct texture_data_t *texture, u16 x, u16 y, u8 r, u8 g,
                      u8 b, u8 a) {
  // check if the component count is 4 since we are setting RGBA values
  ASSERT((texture->components == 4));

  // calculate the index of the pixel
  u32 index = (x + y * texture->width) * texture->components;

  // set each channel of the pixel
  texture->data[index + 0] = r;
  texture->data[index + 1] = g;
  texture->data[index + 2] = b;
  texture->data[index + 3] = a;
}

void texture_data_clear(struct texture_data_t *texture, u16 r, u16 g, u16 b) {
  // check if the component count is 3 since we are setting RGB values
  ASSERT((texture->components == 3));

  // loop over each pixel and set its components
  for (u32 i = 0; i < texture->width * texture->height; i++) {
    texture->data[i * texture->components + 0] = r;
    texture->data[i * texture->components + 1] = g;
    texture->data[i * texture->components + 2] = b;
  }
}

void texture_data_resize(struct texture_data_t *texture, u16 width,
                         u16 height) {
  // free the current pixel data array
  FREE(texture->data);

  // set the new width and height
  texture->width = width;
  texture->height = height;

  // allocate a new array with the new width and height
  // TODO: possible optimization: resize the buffer instead of reallocating
  texture->data = ALLOC_SIZED(u8, width * height * texture->components);
}

void texture_data_destroy(struct texture_data_t *texture) {
  // free the pixel data
  FREE(texture->data);

  // free the struct itself
  FREE(texture);
}

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
