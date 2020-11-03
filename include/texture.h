#pragma noce

#include "core.h"

struct texture_data_t {
  u16 width;
  u16 height;
  u8 components;
  u8* data;
};

struct texture_data_t *texture_data_create(u16 width, u16 height,
                                           u8 components);

void texture_data_set(struct texture_data_t *texture, u16 x, u16 y, u8 r, u8 g,
                      u8 b);
void texture_data_set(struct texture_data_t *texture, u16 x, u16 y, u8 r, u8 g,
                      u8 b, u8 a);

void texture_data_clear(struct texture_data_t *textuer, u16 r, u16 g, u16 b);

void texture_data_destroy(struct texture_data_t *texture);

struct texture_t {
  u32 id;
  struct texture_data_t *data;
};

struct texture_t *texture_create(u16 width, u16 height, u8 components);

struct texture_t *texture_create(struct texture_data_t *data);

void texture_update_data(struct texture_t *texture);

void texture_destroy(struct texture_t *texture);
