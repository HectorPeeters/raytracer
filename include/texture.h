#pragma noce

#include "core.h"

struct texture_data_t {
  u16 width;
  u16 height;
  u8 components;
  u8 *data;
};

struct texture_data_t *texture_data_create(u16 width, u16 height,
                                           u8 components);

void texture_data_set(struct texture_data_t *texture, u16 x, u16 y, u8 r, u8 g,
                      u8 b);
void texture_data_set(struct texture_data_t *texture, u16 x, u16 y, u8 r, u8 g,
                      u8 b, u8 a);

void texture_data_destroy(struct texture_data_t *texture);

struct opengl_texture_t {
  u32 id;
  texture_data_t *data;
};

struct opengl_texture_t *texture_create(u16 width, u16 height, u8 components);

struct opengl_texture_t *texture_create(struct texture_data_t *data);

void texture_update_data(struct opengl_texture_t *texture);

void texture_destroy(struct opengl_texture_t *texture);
