#include "application.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <stdlib.h>

#include "log.h"
#include "opengl_texture.h"
#include "raytrace.h"
#include "serialization.h"
#include "theme.h"

application::application()
    : editor_window(window(1920 / 3 * 2, 1080 / 3 * 2, "Raytracer")),
      running(true), state(render_state(render_settings_t{},
                                        camera(transform(), 70.0f, 0.1f, 100.0f,
                                               1920.0f / 1080.0f))) {}

void application::init() {
  editor_window.init();

  state.init();

  imgui_init();

  theme_cherry();
}

void application::destroy() {
  for (ui_panel *panel : panels) {
    panel->deinit();
  }
  ImGui::DestroyContext();
  editor_window.destroy();
}

bool application::update() {
  editor_window.poll_events();
  running = !editor_window.should_close();

  glClear(GL_COLOR_BUFFER_BIT);

  imgui_begin_frame();

  draw_menu_bar();

  ImGui::ShowDemoWindow();

  for (ui_panel *panel : panels) {
    if (panel->showing) {
      ImGui::Begin(panel->get_title(), &panel->showing);
      panel->draw(*this);
      ImGui::End();
    }
  }

  imgui_end_frame();

  editor_window.update();

  return running;
}

void application::draw_menu_bar() {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Exit")) {
        running = false;
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Window")) {
      for (const auto &panel : panels) {
        if (ImGui::MenuItem(panel->get_title(), nullptr, panel->showing)) {
          panel->showing = !panel->showing;
        }
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
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
