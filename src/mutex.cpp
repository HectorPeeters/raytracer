#include "mutex.h"

#ifdef _X11
mutex::mutex() : mutex_handle(PTHREAD_MUTEX_INITIALIZER) {}

mutex::~mutex() { pthread_mutex_destroy(&mutex_handle); }

void mutex::lock() { pthread_mutex_lock(&mutex_handle); }

void mutex::unlock() { pthread_mutex_unlock(&mutex_handle); }
#elif _WINDOWS
mutex::mutex() : mutex_handle(CreateMutex(NULL, FALSE, NULL)) {}

mutex::~mutex() { CloseHandle(mutex_handle); }

void mutex::lock() { WaitForSingleObject(mutex_handle, INFINITE); }

void mutex::unlock() { ReleaseMutex(mutex_handle); }
#endif
