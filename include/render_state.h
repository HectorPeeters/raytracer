#pragma once

#include "camera.h"
#include "core.h"
#include "raytrace.h"
#include "texture.h"

class render_state {
public:
  render_state(struct render_settings_t settings, camera render_camera);

  void init();
  void destroy();

  void resize(u16 width, u16 height);

  void render_scene();

  inline texture<f32> *get_buffer() { return &buffer; }

public:
  texture<f32> buffer;
  struct render_settings_t settings;
  camera render_camera;
};
