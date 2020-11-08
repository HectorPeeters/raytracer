#pragma once

#include "math/vec2.h"

class render_state;

class render_job {
  public:
  render_job(u16 id, vec2i start_pos, vec2i end_pos, render_state* state)
      : id(id), start_pos(start_pos), end_pos(end_pos),
        size(end_pos - start_pos + 1), state(state) {}

public:
  const u16 id;
  const vec2i start_pos;
  const vec2i end_pos;
  const vec2i size;

  render_state* state;
};
