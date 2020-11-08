#include "thread.h"

#include "log.h"

thread::thread(void (*func)()) : func(func) {}

#ifdef _X11

void thread::start() {
  if (pthread_create(&id, nullptr, (void *(*)(void *))func, nullptr)) {
    LERR("Failed to create thread");
  }
}

void thread::join() {
  if (pthread_join(id, nullptr)) {
    LWARN("Thread froze!!!");
  }
}

#elif _WINDOWS

void thread::start() {
  handle = CreateThread(nullptr, 0, func, nullptr, 0, &id);
  if (!handle) {
    LERR("Failed to create Windows thread");
  }
}

#endif
