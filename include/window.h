#pragma once

#include <glad/glad.h>
// Include GLFW after glad
#include <GLFW/glfw3.h>

#include "core.h"

struct window_t {
  GLFWwindow *glfw_window;
  u16 width;
  u16 height;
};

struct window_t *window_create(u16 width, u16 height, const char *title);
void window_input();
void window_update(struct window_t *window);
bool window_should_close(struct window_t *window);
void window_destroy(struct window_t *window);
