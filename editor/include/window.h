#pragma once

#include <glad/glad.h>
// Include GLFW after glad
#include <GLFW/glfw3.h>

#include "core.h"

class window {
public:
  window(u16 width, u16 height, const char *title);

  void init();
  void destroy();

  void poll_events();
  void update();

  bool should_close();

  inline GLFWwindow *get_glfw_window() { return glfw_window; }

  inline void set_size(u16 w, u16 h) {
    width = w;
    height = h;
  }

private:
  GLFWwindow *glfw_window;
  u16 width;
  u16 height;
  const char *title;
};
