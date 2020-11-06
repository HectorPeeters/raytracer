#include "texture.h"

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
