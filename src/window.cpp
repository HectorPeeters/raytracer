#include "window.h"

#include <stdlib.h>

#include "log.h"

static void on_window_resize(GLFWwindow *window, int width, int height) {
  struct window_t *window_ptr = ALLOC(struct window_t);
  window_ptr->width = width;
  window_ptr->height = height;
  glViewport(0, 0, width, height);
  LDEBG("Window resized: %d, %d", width, height);
}

struct window_t *window_create(u16 width, u16 height, const char *title) {
  if (!glfwInit()) {
    LERR("Could not initialize GLFW");
    return 0;
  }

  struct window_t *window = (struct window_t *)malloc(sizeof(struct window_t));
  window->width = width;
  window->height = height;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window->glfw_window = glfwCreateWindow(width, height, title, 0, 0);

  if (!window->glfw_window) {
    LERR("Could not create GLFW window");
    return 0;
  }

  glfwSetWindowUserPointer(window->glfw_window, window);

  glfwSetWindowSizeCallback(window->glfw_window, on_window_resize);

  glfwMakeContextCurrent(window->glfw_window);

  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  LDEBG("Created GLFW window");

  return window;
}

void window_input() { glfwPollEvents(); }

void window_update(struct window_t *window) {
  glfwSwapBuffers(window->glfw_window);
}

bool window_should_close(struct window_t *window) {
  return glfwWindowShouldClose(window->glfw_window);
}

void window_destroy(struct window_t *window) {
  glfwDestroyWindow(window->glfw_window);
  glfwTerminate();
  FREE(window);

  LDEBG("Destroyed GLFW window");
}
