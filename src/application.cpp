#include "application.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <stdlib.h>

#include "log.h"
#include "raytrace.h"

void setup_imgui(struct window_t *window);
void imgui_beginframe();
void imgui_endframe();

void imgui_draw_raytraced_texture(struct application_t *application);

void imgui_draw_render_settings(struct application_t *application);

struct application_t *application_create() {
  struct application_t *result = ALLOC(struct application_t);

  result->window = window_create(1920 / 3 * 2, 1080 / 3 * 2, "Raytracer");
  result->running = 1;
  result->state = render_state_create("data/scene.json");
  result->texture = texture_create(result->state.texture);

  for (int i = 0; i < 1920; i++) {
    for (int j = 0; j < 1080; j++)
      texture_data_set(result->state.texture, i, j, u8(i / 1920.0 * 255.0),
                       u8(j / 1920.0 * 255.0), 255);
  }
  texture_update_data(result->texture);

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

  imgui_draw_raytraced_texture(application);
  imgui_draw_render_settings(application);

  imgui_endframe();

  window_update(application->window);

  return application->running;
}

void imgui_beginframe() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

  ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                  ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  window_flags |=
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

  if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
    window_flags |= ImGuiWindowFlags_NoBackground;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

  ImGui::Begin("DockSpace Demo", 0, window_flags);
  ImGui::PopStyleVar();

  ImGui::PopStyleVar(2);

  // DockSpace
  ImGuiIO &io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
    ImGuiID dockspace_id = ImGui::GetID("RootDockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
  }

  ImGui::End();
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

void imgui_draw_raytraced_texture(struct application_t *application) {
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
  ImGui::Begin("Raytrace View");

  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

  float aspect = application->texture->data->width /
                 float(application->texture->data->height);

  int smallestSize = viewportPanelSize.x / aspect < viewportPanelSize.y
                         ? viewportPanelSize.x / aspect
                         : viewportPanelSize.y;

  ImVec2 image_pos = ImVec2(
      ImGui::GetCursorPos().x +
          (ImGui::GetContentRegionAvail().x - smallestSize * aspect) * 0.5,
      ImGui::GetCursorPos().y +
          (ImGui::GetContentRegionAvail().y - smallestSize) * 0.5);
  ImGui::SetCursorPos(image_pos);

  ImGui::Image((void *)(u64)application->texture->id,
               ImVec2(smallestSize * aspect, smallestSize), ImVec2(0, 1),
               ImVec2(1, 0));

  ImGui::End();
  ImGui::PopStyleVar();
}

void imgui_draw_render_settings(struct application_t *application) {
  ImGui::Begin("Settings");

  {
    // Resolution input field
    i32 resolution[2]{application->state.settings.width,
                      application->state.settings.height};
    if (ImGui::InputInt2("Resolution", resolution)) {
      if (application->state.settings.width != resolution[0] ||
          application->state.settings.height != resolution[1]) {

        application->state.settings.width = resolution[0];
        application->state.settings.height = resolution[1];

        texture_data_resize(application->state.texture, resolution[0],
                            resolution[1]);
      }
    }
  }

  {
    // Samples per pixel input field
    i32 value = application->state.settings.samples_per_pixel;
    ImGui::SliderInt("Samples Per Pixel", &value, 1, 1000);
    application->state.settings.samples_per_pixel = value;
  }

  {
  // Render button
  if (ImGui::Button("Render")) {
    for (int i = 0; i < application->state.texture->width; i++) {
      for (int j = 0; j < application->state.texture->height; j++) {
        glm::vec3 result{0.0};
        for (int s = 0; s < application->state.settings.samples_per_pixel; s++)
          result += glm::vec3{rand() % 255, rand() % 255, rand() % 255};

        result /= application->state.settings.samples_per_pixel;

        texture_data_set(application->state.texture, i, j, result.x, result.y,
                         result.z);
      }
    }
    texture_update_data(application->texture);
  }
  }

  ImGui::End();
}

void application_destroy(struct application_t *application) {
  ImGui::DestroyContext();

  window_destroy(application->window);

  FREE(application);
}
