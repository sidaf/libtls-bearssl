#ifndef PTHREAD_H
#define PTHREAD_H

/*
#define _WINSOCKAPI_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef __MINGW32__
#include <errno.h>
#endif

// https://gist.github.com/informationsea/f63c2b3854b20bd540ab

typedef struct pthread_mutex_tag {
  HANDLE handle;
} pthread_mutex_t;

typedef struct pthread_mutexattr_tag {
  int attr;
} pthread_mutexattr_t;

int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
*/

// https://nachtimwald.com/2019/04/05/cross-platform-thread-wrapper/

#ifdef _WIN32
#define _WINSOCKAPI_
#define WIN32_LEAN_AND_MEAN
# include <windows.h>
#else
# include <pthread.h>
#endif

#ifdef _WIN32
typedef CRITICAL_SECTION pthread_mutex_t;
typedef void pthread_mutexattr_t;

#endif

#ifdef _WIN32

int pthread_mutex_init(pthread_mutex_t *mutex, pthread_mutexattr_t *attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);

#endif

#endif //PTHREAD_H
