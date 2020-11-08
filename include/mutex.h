#pragma once

#ifdef _X11
#include <pthread.h>
#elif _WINDOWS
#include <Windows.h>
#else
#error Unsupported platform!
#endif

class mutex {
public:
  mutex() ;
  ~mutex(); 

  void lock();
  void unlock();

private:
#ifdef _X11
  pthread_mutex_t mutex_handle;
#elif _WINDOWS
  HANDLE mutex_handle;
#endif
};
