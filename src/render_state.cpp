#include "render_state.h"

#include "sphere.h"
#include "thread.h"

render_state::render_state(struct render_settings_t settings,
                           camera render_camera)
    : buffer(settings.width, settings.height, 4), settings(settings),
      render_camera(render_camera) {}

void render_state::init() {
  buffer.init();
  populate_jobs_queue();
}

void render_state::destroy() { buffer.destroy(); }

void render_state::populate_jobs_queue() {
  queue_mutex.lock();

  jobs_queue = std::vector<render_job>();

  const u16 job_size = settings.width / 16;

  u16 id;
  for (u16 y = 0; y < settings.height; y += job_size) {
    for (u16 x = 0; x < settings.width; x += job_size) {
      vec2i start(x, y);
      vec2i end(MIN(x + job_size, settings.width),
                MIN(y + job_size, settings.height));

      LDEBG("%d %d", x, y);

      render_job job(id, start, end, this);
      jobs_queue.push_back(job);

      id++;
    }
  }

  queue_mutex.unlock();
}

render_job render_state::get_next_job() {
  queue_mutex.lock();
  render_job job = jobs_queue[job_index];
  job_index++;
  queue_mutex.unlock();

  return job;
}

bool render_state::jobs_finished() {
  return job_index == jobs_queue.size();
}

void render_state::resize(u16 width, u16 height) {
  buffer.resize(width, height);

  settings.width = width;
  settings.height = height;

  render_camera.resize(width, height);

  populate_jobs_queue();
}

static void render_single_job(render_state *state, render_job job) {
  sphere sphere(transform(vec3f(0.0f, 0.0f, -2.0f), vec3f(0.0f, 0.0f, 0.0f),
                          vec3f(1.0f, 1.0f, 1.0f)));
  sphere.object_transform.update_matrices();

  // loop over each pixel in the scene
  for (int j = job.start_pos.y; j < job.end_pos.y; j++) {
    for (int i = job.start_pos.x; i < job.end_pos.x; i++) {
      // the final color of the pixel
      vec4f result(0.0f);

      // loop for each sample of this pixel
      for (int s = 0; s < state->settings.samples_per_pixel; s++) {
        f32 u = (i + (rand() / (f32)RAND_MAX)) / (f32)state->buffer.width;
        f32 v = (j + (rand() / (f32)RAND_MAX)) / (f32)state->buffer.height;

        ray_t camera_ray = state->render_camera.get_ray(u, v);

        bool hit = sphere.intersect(camera_ray);

        if (hit) {
          result += vec4f(0.0f, 0.0f, 1.0f, 1.0f);
        } else {
          vec3f dir = state->render_camera.get_ray(u, v).direction;
          f32 t = 0.5f * (dir.y + 1.0f);

          result += (1.0f - t) * vec4f(1.0f, 1.0f, 1.0f, 1.0f) +
                    t * vec4f(0.5f, 0.7f, 1.0f, 1.0f);
        }
      }

      // average all samples
      result /= state->settings.samples_per_pixel;

      // set the pixel value
      state->buffer.set(i, j, result);
    }
  }
}

static void run_render_thread(render_state *state) {
  while (!state->jobs_finished()) {
    render_job job = state->get_next_job();
    render_single_job(state, job);
  }
}

void render_state::render_scene() {
  buffer.clear(vec4f(0.3));
  job_index = 0;

  for (u8 i = 0; i < 8; i++) {
    thread<render_state> render_thread(run_render_thread);
    render_thread.start(this);
  }
}
