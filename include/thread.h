#pragma once

#ifdef _X11
#include <pthread.h>
#elif _WINDOWS
#include <Windows.h>
#else
#error Unsupported platform !
#endif

#include "log.h"

template <typename T> class thread {
public:
  thread(void (*func)(T *)) : func(func) {}

#ifdef _X11
  void start(T *data) {
    if (pthread_create(&id, nullptr, (void *(*)(void *))func, (void*)data)) {
      LERR("Failed to create thread");
    }
  }

  void join() {
    if (pthread_join(id, nullptr)) {
      LWARN("Thread froze!!!");
    }
  }
#elif _WINDOWS
  void thread::start(T *data) {
    handle = CreateThread(nullptr, 0, func, nullptr, 0, &id);
    if (!handle) {
      LERR("Failed to create Windows thread");
    }
  }
#endif

private:
#ifdef _X11
  pthread_t id;
#elif _WINDOWS
  HANDLE handle;
  DWORD id;
#endif

  void (*func)(T *);
};
