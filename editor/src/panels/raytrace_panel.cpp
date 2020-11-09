#include "panels/raytrace_panel.h"

#include <imgui.h>
#include <imgui_internal.h>

raytrace_panel::raytrace_panel()
    : ui_panel("Raytrace"), texture(4, 1920, 1080) {}
raytrace_panel::~raytrace_panel() {}

void raytrace_panel::init() { texture.init(); }

void raytrace_panel::draw(application &app) {
  render_state &state = app.state;

  texture.update_contents(state.buffer.data);

  ImGui::Columns(2);
  {

    if (ImGui::BeginMenuBar()) {
      if (ImGui::MenuItem("Save")) {
      }
      ImGui::EndMenuBar();
    }

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

    float aspect = texture.width / float(texture.height);

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
  }

  ImGui::NextColumn();

  ImGui::BeginChild("settings");
  {
    // Resolution input field
    i32 resolution[2]{state.settings.width, state.settings.height};

    if (ImGui::InputInt2("Resolution", resolution,
                         ImGuiInputTextFlags_EnterReturnsTrue)) {
      if (state.settings.width != resolution[0] ||
          state.settings.height != resolution[1]) {

        state.settings.width = resolution[0];
        state.settings.height = resolution[1];

        texture.resize(resolution[0], resolution[1]);
        state.resize(resolution[0], resolution[1]);
        state.buffer.resize(resolution[0], resolution[1]);
      }
    }
  }

  {
    // Samples per pixel input field
    i32 samples = state.settings.samples_per_pixel;
    ImGui::SliderInt("Samples Per Pixel", &samples, 1, 1000);
    state.settings.samples_per_pixel = samples;
  }

  {
    // Amount of threads to use for rendering
    i32 threads = state.settings.thread_count;
    ImGui::SliderInt("Threads", &threads, 1, 16);
    state.settings.thread_count = threads;
  }

  {
    // Render button
    if (!state.jobs_finished())
      ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
    if (ImGui::Button("Render")) {
      state.render_scene();
    }
    if (!state.jobs_finished())
      ImGui::PopItemFlag();
  }
  ImGui::EndChild();

  ImGui::Columns(1);
}

void raytrace_panel::deinit() { texture.destroy(); }
