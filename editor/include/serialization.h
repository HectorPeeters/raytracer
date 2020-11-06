#pragma once

#include <parson.h>

#include "raytrace.h"

JSON_Object *read_json_file(const char *file);

struct render_settings_t deserialize_render_settings(JSON_Object *root);
