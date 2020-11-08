#pragma once

#include "core.h"

class framebuffer {
public:
  framebuffer(u32 width, u32 height);

  void init();
  void destroy();

  void resize(u32 width, u32 height);

  void bind();
  void unbind();

private:
  u32 width, height;

  u32 fbo_id;
  u32 color_id;
  u32 render_id;
};
