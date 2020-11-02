#include "texture.h"

struct texture_t *texture_create(u16 width, u16 height, u8 components) {
  struct texture_t *result = ALLOC(texture_t);

  result->width = width;
  result->height = height;
  result->components = components;
  result->data = ALLOC_SIZED(u8, width * height * components);

  return result;
}

void texture_set(struct texture_t *texture, u16 x, u16 y, u8 r, u8 g, u8 b) {
  ASSERT(texture->components == 3);

  u32 index = (x + y * texture->width) * texture->components;
  texture->data[index + 0] = r;
  texture->data[index + 1] = g;
  texture->data[index + 2] = b;
}
void texture_set(struct texture_t *texture, u16 x, u16 y, u8 r, u8 g, u8 b,
                 u8 a) {
  ASSERT(texture->components == 4);

  u32 index = (x + y * texture->width) * texture->components;
  texture->data[index + 0] = r;
  texture->data[index + 1] = g;
  texture->data[index + 2] = b;
  texture->data[index + 3] = a;
}

void texture_destroy(struct texture_t *texture) {
  FREE(texture->data);
  FREE(texture);
}
