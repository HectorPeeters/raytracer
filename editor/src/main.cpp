#include "application.h"
#include "log.h"

int main() {
  application app;

  LINFO("Startup complete");

  while (app.update()) {
  }

  LINFO("Shutting down...");

  return 0;
}
