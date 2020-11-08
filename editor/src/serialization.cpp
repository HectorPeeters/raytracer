#include "serialization.h"

#include "core.h"

JSON_Object *read_json_file(const char *file) {
  JSON_Value *value = json_parse_file(file);

  return json_value_get_object(value);
}

#define READ_NUMBER(object, name, type)                                        \
  (type)(json_number(json_object_get_value(object, name)))

struct render_settings_t deserialize_render_settings(JSON_Object *root) {
  JSON_Object *settings_value = json_object_get_object(root, "render_settings");

  u16 width = READ_NUMBER(settings_value, "width", u16);
  u16 height = READ_NUMBER(settings_value, "height", u16);
  u32 samples_per_pixel = READ_NUMBER(settings_value, "samples_per_pixel", u32);
  u8 threads = READ_NUMBER(settings_value, "threads", u8);

  return render_settings_t{width, height, samples_per_pixel, threads};
}
