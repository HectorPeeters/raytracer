#pragma once

#ifdef _X11
#include <pthread.h>
#elif _WINDOWS
#include <Windows.h>
#else
#error Unsupported platform !
#endif

class thread {
public:
  thread(void (*func)());

  void start();
  void join();

private:
#ifdef _X11
  pthread_t id;
#elif _WINDOWS
  HANDLE handle;
  DWORD id;
#endif

  void (*func)();
};
