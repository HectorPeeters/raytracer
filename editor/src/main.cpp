#include "application.h"
#include "log.h"

int main() {
  application app;
  app.init();

  LINFO("Startup complete");

  while (app.update()) {
  }

  LINFO("Shutting down...");

  app.destroy();

  return 0;
}
