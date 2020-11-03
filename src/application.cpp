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

  result->window = window_create(1920 / 3 * 2, 1080 / 3 * 2, "Raytracer");
  result->running = 1;
  result->texture = texture_create(texture_data_create(512, 512, 3));

  for (u16 i = 0; i < 512; i++) {
    for (u16 j = 0; j < 512; j++) {
      texture_data_set(result->texture->data, i, j, u8(i / 2), u8(j / 2),
                       u8(255));
    }
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

  // Rendering here!
  ImGui::ShowDemoWindow();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
  ImGui::Begin("Texture Test");

  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  
  int smallestSize = viewportPanelSize.x < viewportPanelSize.y ? viewportPanelSize.x : viewportPanelSize.y;

  ImVec2 image_pos = ImVec2(
    ImGui::GetCursorPos().x + (ImGui::GetContentRegionAvail().x - smallestSize) * 0.5,
    ImGui::GetCursorPos().y + (ImGui::GetContentRegionAvail().y - smallestSize) * 0.5
  );
  ImGui::SetCursorPos(image_pos);

  ImGui::Image((void*)(u64)application->texture->id, ImVec2(smallestSize, smallestSize), ImVec2(0, 1), ImVec2(1, 0));

  ImGui::End();
  ImGui::PopStyleVar();

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

void application_destroy(struct application_t *application) {
  ImGui::DestroyContext();

  window_destroy(application->window);

  FREE(application);
}
