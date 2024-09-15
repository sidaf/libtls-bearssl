#include "pthread.h"

/*
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
  HANDLE handle = CreateMutexA(NULL,FALSE,NULL);
  if(handle != NULL){
    mutex->handle = handle;
    return 0;
  }else{
    return 1;
  }
}

int pthread_mutex_lock(pthread_mutex_t *mutex)
{
  DWORD retvalue = WaitForSingleObject(mutex->handle, INFINITE);
  if(retvalue == WAIT_OBJECT_0){
    return 0;
  }else{
    return EINVAL;
  }
}

int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
  return !ReleaseMutex(mutex->handle);
}

*/

int pthread_mutex_init(pthread_mutex_t *mutex, pthread_mutexattr_t *attr)
{
  (void)attr;

  if (mutex == NULL)
    return 1;

  InitializeCriticalSection(mutex);
  return 0;
}

int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
  if (mutex == NULL)
    return 1;
  DeleteCriticalSection(mutex);
  return 0;
}

int pthread_mutex_lock(pthread_mutex_t *mutex)
{
  if (mutex == NULL)
    return 1;
  EnterCriticalSection(mutex);
  return 0;
}

int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
  if (mutex == NULL)
    return 1;
  LeaveCriticalSection(mutex);
  return 0;
}