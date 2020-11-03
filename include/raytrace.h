#pragma once

#include "texture.h"

struct render_settings_t {
    u16 width;
    u16 height;
    i32 samples_per_pixel;
};

struct render_state_t {
    struct texture_data_t* texture;
    struct render_settings_t settings;
};

struct render_state_t render_state_create();