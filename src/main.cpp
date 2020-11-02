#include "application.h"
#include "log.h"

#include "ray.h"

int main() {
  struct application_t *application = application_create();

  

  LINFO("Startup complete");

  while (application_update(application)) {
  }

  LINFO("Shutting down...");

  application_destroy(application);

  return 0;
}
