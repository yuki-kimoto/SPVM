// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_mutex.h"

#if defined(_WIN32)

#include <windows.h>

void SPVM_MUTEX_init(SPVM_MUTEX* mutex) { InitializeSRWLock((SRWLOCK*)mutex->mutex); }
void SPVM_MUTEX_destroy(SPVM_MUTEX* mutex) { }
void SPVM_MUTEX_lock(SPVM_MUTEX* mutex) { AcquireSRWlockExclusive((SRWLOCK*)mutex->mutex); }
void SPVM_MUTEX_unlock(SPVM_MUTEX* mutex) { ReleaseSRWlockExclusive((SRWLOCK*)mutex->mutex); }
void SPVM_MUTEX_reader_lock(SPVM_MUTEX* mutex) { AcquireSRWlockShared((SRWLOCK*)mutex->mutex); }
void SPVM_MUTEX_reader_unlock(SPVM_MUTEX* mutex) { ReleaseSRWlockShared((SRWLOCK*)mutex->mutex); }

#else

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define SAFE_PTHREAD(fncall)    \
  do {                          \
    if ((fncall) != 0) abort(); \
  } while (0)

void SPVM_MUTEX_init(SPVM_MUTEX* mutex) { SAFE_PTHREAD(pthread_rwlock_init((pthread_rwlock_t*)mutex->mutex, NULL)); }
void SPVM_MUTEX_destroy(SPVM_MUTEX* mutex) { SAFE_PTHREAD(pthread_rwlock_destroy((pthread_rwlock_t*)mutex->mutex)); }
void SPVM_MUTEX_lock(SPVM_MUTEX* mutex) { SAFE_PTHREAD(pthread_rwlock_wrlock((pthread_rwlock_t*)mutex->mutex)); }
void SPVM_MUTEX_unlock(SPVM_MUTEX* mutex) { SAFE_PTHREAD(pthread_rwlock_unlock((pthread_rwlock_t*)mutex->mutex)); }
void SPVM_MUTEX_reader_lock(SPVM_MUTEX* mutex) { SAFE_PTHREAD(pthread_rwlock_rdlock((pthread_rwlock_t*)mutex->mutex)); }
void SPVM_MUTEX_reader_unlock(SPVM_MUTEX* mutex) { SAFE_PTHREAD(pthread_rwlock_unlock((pthread_rwlock_t*)mutex->mutex)); }

#undef SAFE_PTHREAD

#endif
