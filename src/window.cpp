#include "window.h"

#include <stdlib.h>

#include "log.h"

static void on_window_resize(GLFWwindow *window, int width, int height) {
  // get a pointer to our own window struct from GLFW
  struct window_t *window_ptr =
      (struct window_t *)glfwGetWindowUserPointer(window);

  // set window size
  window_ptr->width = width;
  window_ptr->height = height;

  // set GLFW viewport
  glViewport(0, 0, width, height);

  LDEBG("Window resized: %d, %d", width, height);
}

struct window_t *window_create(u16 width, u16 height, const char *title) {
  // try and initialize GLFW
  if (!glfwInit()) {
    LERR("Could not initialize GLFW");
    return 0;
  }

  // allocate a new window_t struct
  struct window_t *window = (struct window_t *)malloc(sizeof(struct window_t));

  // set the size of the window
  window->width = width;
  window->height = height;

  // set OpenGL version and profile
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create GLFW window
  window->glfw_window = glfwCreateWindow(width, height, title, 0, 0);

  // check if GLFW window has been created correctly
  if (!window->glfw_window) {
    LERR("Could not create GLFW window");
    return 0;
  }

  // give GLFW a pointer to our window_t struct for use in callbacks
  glfwSetWindowUserPointer(window->glfw_window, window);

  // set the resize callback
  glfwSetWindowSizeCallback(window->glfw_window, on_window_resize);

  // switch the context
  glfwMakeContextCurrent(window->glfw_window);

  // load OpenGL functions
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  LDEBG("Created GLFW window");

  return window;
}

void window_input() {
  // poll GLFW events
  glfwPollEvents();
}

void window_update(struct window_t *window) {
  // swap buffers to show result to screen
  glfwSwapBuffers(window->glfw_window);
}

bool window_should_close(struct window_t *window) {
  // check if the GLFW window should be closed
  return glfwWindowShouldClose(window->glfw_window);
}

void window_destroy(struct window_t *window) {
  // destroy the GLFW window
  glfwDestroyWindow(window->glfw_window);

  // destroy the GLFW context
  glfwTerminate();

  // delete the window struct
  FREE(window);

  LDEBG("Destroyed GLFW window");
}
