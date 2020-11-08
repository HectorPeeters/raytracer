#pragma once

#include "core.h"
#include "opengl_texture.h"
#include "raytrace.h"
#include "window.h"

class application {
public:
  application();
  ~application();
  bool update();

private:
  void imgui_init();
  void imgui_destroy();

  void imgui_begin_frame();
  void imgui_end_frame();

  void imgui_draw_raytraced_texture();
  void imgui_draw_render_settings();

private:
  bool running;
  struct window_t *window;
  struct render_state_t state;
  opengl_texture<f32> texture;
};
