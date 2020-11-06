#pragma once

#include "core.h"
#include "texture.h"

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
