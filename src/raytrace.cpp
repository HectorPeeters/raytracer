#include "raytrace.h"

struct render_state_t render_state_create() {
    u16 width = 1920;
    u16 height = 1080;
    return render_state_t {
        texture_data_create(width, height, 3),
        {
            .width = width,
            .height = height,
            .samples_per_pixel = 1,
        }
    };
}