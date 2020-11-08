#include "window.h"

#include <stdlib.h>

#include "log.h"

static void on_window_resize(GLFWwindow *glfw_window, int width, int height) {
  // get a pointer to our own window struct from GLFW
  window *window_ptr = (window *)glfwGetWindowUserPointer(glfw_window);

  // set window size
  window_ptr->set_size(width, height);

  // set GLFW viewport
  glViewport(0, 0, width, height);

  LDEBG("Window resized: %d, %d", width, height);
}

window::window(u16 width, u16 height, const char *title)
    : width(width), height(height), title(title) {}

void window::init() {
  // try and initialize GLFW
  if (!glfwInit()) {
    LERR("Could not initialize GLFW");
    return;
  }

  // set OpenGL version and profile
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create GLFW window
  glfw_window = glfwCreateWindow(width, height, title, 0, 0);

  // check if GLFW window has been created correctly
  if (!glfw_window) {
    LERR("Could not create GLFW window");
    return;
  }

  // give GLFW a pointer to our window_t struct for use in callbacks
  glfwSetWindowUserPointer(glfw_window, this);

  // set the resize callback
  glfwSetWindowSizeCallback(glfw_window, on_window_resize);

  // switch the context
  glfwMakeContextCurrent(glfw_window);

  // load OpenGL functions
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  LDEBG("Created GLFW window");
}

void window::destroy() {
  // destroy the GLFW window
  glfwDestroyWindow(glfw_window);

  // destroy the GLFW context
  glfwTerminate();

  LDEBG("Destroyed GLFW window");
}

void window::poll_events() {
  // poll GLFW events
  glfwPollEvents();
}

void window::update() {
  // swap buffers to show result to screen
  glfwSwapBuffers(glfw_window);
}

bool window::should_close() {
  // check if the GLFW window should be closed
  return glfwWindowShouldClose(glfw_window);
}
