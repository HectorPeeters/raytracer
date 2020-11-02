#pragma noce

#include "core.h"

struct texture_t {
  u16 width;
  u16 height;
  u8 components;
  u8 *data;
};

struct texture_t *texture_create(u16 width, u16 height, u8 components);

void texture_set(struct texture_t *texture, u16 x, u16 y, u8 r, u8 g, u8 b);
void texture_set(struct texture_t *texture, u16 x, u16 y, u8 r, u8 g, u8 b,
                 u8 a);

void texture_destroy(struct texture_t *texture);
