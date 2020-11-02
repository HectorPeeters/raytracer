#include "application.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#include "log.h"

void setup_imgui(struct window_t *window);
void imgui_beginframe();
void imgui_endframe();

struct application_t *application_create() {
  struct application_t *result = ALLOC(struct application_t);

  result->window = window_create(1920 / 2, 1080 / 2, "Raytracer");
  result->running = 1;

  setup_imgui(result->window);

  return result;
}

void setup_imgui(struct window_t *window) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  ImGui::StyleColorsDark();

  ImGuiStyle &style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  if (!ImGui_ImplGlfw_InitForOpenGL(window->glfw_window, true)) {
    LERR("Failed to initialize ImGui GLFW");
    return;
  }

  if (!ImGui_ImplOpenGL3_Init("#version 410")) {
    LERR("Failed to initialize OpenGL3 GLFW");
    return;
  }
}

bool application_update(struct application_t *application) {
  window_input();
  application->running = !window_should_close(application->window);

  glClear(GL_COLOR_BUFFER_BIT);

  imgui_beginframe();

  // Rendering here!
  ImGui::ShowDemoWindow();

  imgui_endframe();

  window_update(application->window);

  return application->running;
}

void imgui_beginframe() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void imgui_endframe() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  ImGuiIO &io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow *backup_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_context);
  }
}

void application_destroy(struct application_t *application) {
  ImGui::DestroyContext();

  window_destroy(application->window);

  FREE(application);
}
