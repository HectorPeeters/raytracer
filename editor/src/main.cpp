#include "application.h"
#include "log.h"
#include "panels/raytrace_panel.h"

int main() {
  application app;
  app.init();
  app.add_panel<raytrace_panel>();

  LINFO("Startup complete");

  while (app.update()) {
  }

  LINFO("Shutting down...");

  app.destroy();

  return 0;
}
