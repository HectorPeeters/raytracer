#include "application.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <stdlib.h>

#include "log.h"
#include "opengl_texture.h"
#include "raytrace.h"
#include "serialization.h"
#include "theme.h"

application::application()
    : editor_window(window(1920 / 3 * 2, 1080 / 3 * 2, "Raytracer")),
      running(true),
      state(render_state_create(render_settings_create(1920, 1080, 1))),
      texture(opengl_texture<f32>(&state.buffer)) {}

void application::init() {
  editor_window.init();

texture.init();

  for (int i = 0; i < state.buffer.width; i++) {
    for (int j = 0; j < state.buffer.height; j++) {
      state.buffer.set(i, j,
                       vec4f(i / (f32)state.buffer.width,
                             j / (f32)state.buffer.height, 1.0f, 1.0f));
    }
  }

  texture.update_contents();

  imgui_init();

  theme_cherry();
}

void application::destroy() {
  texture.destroy();
  ImGui::DestroyContext();
  editor_window.destroy();
}

bool application::update() {
  editor_window.poll_events();
  running = !editor_window.should_close();

  glClear(GL_COLOR_BUFFER_BIT);

  imgui_begin_frame();

  imgui_draw_raytraced_texture();
  imgui_draw_render_settings();

  imgui_end_frame();

  editor_window.update();

  return running;
}

void application::imgui_init() {
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

  if (!ImGui_ImplGlfw_InitForOpenGL(editor_window.get_glfw_window(), true)) {
    LERR("Failed to initialize ImGui GLFW");
    return;
  }

  if (!ImGui_ImplOpenGL3_Init("#version 410")) {
    LERR("Failed to initialize OpenGL3 GLFW");
    return;
  }
}

void application::imgui_begin_frame() {
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

void application::imgui_end_frame() {
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

void application::imgui_draw_raytraced_texture() {
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
  ImGui::Begin("Raytrace View");

  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

  float aspect =
      texture.texture_data->width / float(texture.texture_data->height);

  int smallestSize = viewportPanelSize.x / aspect < viewportPanelSize.y
                         ? viewportPanelSize.x / aspect
                         : viewportPanelSize.y;

  ImVec2 image_pos = ImVec2(
      ImGui::GetCursorPos().x +
          (ImGui::GetContentRegionAvail().x - smallestSize * aspect) * 0.5,
      ImGui::GetCursorPos().y +
          (ImGui::GetContentRegionAvail().y - smallestSize) * 0.5);
  ImGui::SetCursorPos(image_pos);

  ImGui::Image((void *)(u64)texture.id,
               ImVec2(smallestSize * aspect, smallestSize), ImVec2(0, 1),
               ImVec2(1, 0));

  ImGui::End();
  ImGui::PopStyleVar();
}

void application::imgui_draw_render_settings() {
  ImGui::Begin("Settings");

  {
    // Resolution input field
    i32 resolution[2]{state.settings.width, state.settings.height};

    if (ImGui::InputInt2("Resolution", resolution)) {
      if (state.settings.width != resolution[0] ||
          state.settings.height != resolution[1]) {

        state.settings.width = resolution[0];
        state.settings.height = resolution[1];

        texture.resize(resolution[0], resolution[1]);
      }
    }
  }

  {
    // Samples per pixel input field
    i32 value = state.settings.samples_per_pixel;
    ImGui::SliderInt("Samples Per Pixel", &value, 1, 1000);
    state.settings.samples_per_pixel = value;
  }

  {
    // Render button
    if (ImGui::Button("Render")) {
      render_scene(&state);
      texture.update_contents();
    }
  }

  ImGui::End();
}
