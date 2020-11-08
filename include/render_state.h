#pragma once

#include "camera.h"
#include "core.h"
#include "mutex.h"
#include "raytrace.h"
#include "render_job.h"
#include "texture.h"

#include <vector>

class render_state {
public:
  render_state(struct render_settings_t settings, camera render_camera);

  void init();
  void destroy();

  void populate_jobs_queue();
  render_job get_next_job();
  bool jobs_finished();

  void resize(u16 width, u16 height);

  void render_scene();

public:
  texture<f32> buffer;
  struct render_settings_t settings;
  camera render_camera;

  mutex queue_mutex;
  std::vector<render_job> jobs_queue;
  u32 job_index = 0;
};
