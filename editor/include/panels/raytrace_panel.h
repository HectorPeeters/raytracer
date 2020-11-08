#pragma once

#include "application.h"
#include "opengl_texture.h"
#include "ui_panel.h"

class raytrace_panel : public ui_panel {
public:
  raytrace_panel();
  ~raytrace_panel();

  void init();
  void draw(application &app);
  void deinit();

private:
    opengl_texture<f32> texture;
};
