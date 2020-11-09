#pragma once

#include <vector>

#include "core.h"
#include "opengl_texture.h"
#include "raytrace.h"
#include "render_state.h"
#include "ui_panel.h"
#include "window.h"

class application {
public:
  application();

  void init();
  void destroy();

  bool update();

  template <class T> void add_panel() {
    T *value = new T();
    value->init();
    panels.push_back(value);
  }

private:
  void draw_menu_bar();

  void imgui_init();
  void imgui_destroy();

  void imgui_begin_frame();
  void imgui_end_frame();

public:
  bool running;
  window editor_window;
  render_state state;

private:
  std::vector<ui_panel *> panels;
};
