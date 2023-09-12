// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_MUTEX_H
#define SPVM_MUTEX_H

#define _GNU_SOURCE

struct spvm_mutex;
typedef struct spvm_mutex SPVM_MUTEX;

#if defined(_WIN32)

#include <windows.h>

struct spvm_mutex {
  SRWLOCK mutex;
};

void SPVM_MUTEX_init(SPVM_MUTEX* mutex) { InitializeSRWLock(mutex->mutex); }
void SPVM_MUTEX_destroy(SPVM_MUTEX* mutex) { }
void SPVM_MUTEX_lock(SPVM_MUTEX* mutex) { AcquireSRWlockExclusive(mutex->mutex); }
void SPVM_MUTEX_unlock(SPVM_MUTEX* mutex) { ReleaseSRWlockExclusive(mutex->mutex); }
void SPVM_MUTEX_reader_lock(SPVM_MUTEX* mutex) { AcquireSRWlockShared(mutex->mutex); }
void SPVM_MUTEX_reader_unlock(SPVM_MUTEX* mutex) { ReleaseSRWlockShared(mutex->mutex); }

#else

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

struct spvm_mutex {
  pthread_rwlock_t* mutex;
};

#define SAFE_PTHREAD(fncall)    \
  do {                          \
    if ((fncall) != 0) abort(); \
  } while (0)

void SPVM_MUTEX_init(SPVM_MUTEX* mutex) { SAFE_PTHREAD(pthread_rwlock_init(mutex->mutex, NULL)); }
void SPVM_MUTEX_destroy(SPVM_MUTEX* mutex) { SAFE_PTHREAD(pthread_rwlock_destroy(mutex->mutex)); }
void SPVM_MUTEX_lock(SPVM_MUTEX* mutex) { SAFE_PTHREAD(pthread_rwlock_wrlock(mutex->mutex)); }
void SPVM_MUTEX_unlock(SPVM_MUTEX* mutex) { SAFE_PTHREAD(pthread_rwlock_unlock(mutex->mutex)); }
void SPVM_MUTEX_reader_lock(SPVM_MUTEX* mutex) { SAFE_PTHREAD(pthread_rwlock_rdlock(mutex->mutex)); }
void SPVM_MUTEX_reader_unlock(SPVM_MUTEX* mutex) { SAFE_PTHREAD(pthread_rwlock_unlock(mutex->mutex)); }

#undef SAFE_PTHREAD

#endif

#endif  // SPVM_MUTEX_H
