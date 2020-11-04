#pragma noce

#include "core.h"

struct texture_data_t {
  // the width of the texture
  u16 width;

  // the height of the texture
  u16 height;

  // the amount of components each pixel has: rgb -> 3, rgba -> 4
  u8 components;

  // the pixel data of the texture
  u8 *data;
};

struct texture_data_t *texture_data_create(u16 width, u16 height,
                                           u8 components);

void texture_data_set(struct texture_data_t *texture, u16 x, u16 y, u8 r, u8 g,
                      u8 b);
void texture_data_set(struct texture_data_t *texture, u16 x, u16 y, u8 r, u8 g,
                      u8 b, u8 a);

void texture_data_clear(struct texture_data_t *texture, u16 r, u16 g, u16 b);

void texture_data_resize(struct texture_data_t *texture, u16 width, u16 height);

void texture_data_destroy(struct texture_data_t *texture);

struct texture_t {
  // the opengl id of the texture
  u32 id;
  
  // a pointer to the actual texture data
  struct texture_data_t *data;
};

struct texture_t *texture_create(u16 width, u16 height, u8 components);

struct texture_t *texture_create(struct texture_data_t *data);

void texture_resize(struct texture_t *texture, u16 width, u16 height);

void texture_update_data(struct texture_t *texture);

void texture_destroy(struct texture_t *texture);
