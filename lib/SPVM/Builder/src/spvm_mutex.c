// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_mutex.h"
#include "spvm_allocator.h"

#if defined(_WIN32)

#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#include <windows.h>
#include <synchapi.h>

void SPVM_MUTEX_init(void* mutex) {
  
  InitializeSRWLock((SRWLOCK*)mutex);
}

void SPVM_MUTEX_destroy(void* mutex) {
  
}

void SPVM_MUTEX_lock (void* mutex) {
  AcquireSRWLockExclusive((SRWLOCK*)mutex);
}

void SPVM_MUTEX_unlock (void* mutex) {
  ReleaseSRWLockExclusive((SRWLOCK*)mutex);
}

void SPVM_MUTEX_reader_lock (void* mutex) {
  AcquireSRWLockShared((SRWLOCK*)mutex);
}

void SPVM_MUTEX_reader_unlock (void* mutex) {
  ReleaseSRWLockShared((SRWLOCK*)mutex);
}

int32_t SPVM_MUTEX_size () {
  return sizeof(SRWLOCK);
}

#else

// Use _GNU_SOURCE to enable pthread_rwlock_t and related functions,
// which are not part of the strict C99 standard but available as POSIX extensions.
#define _GNU_SOURCE

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define SAFE_PTHREAD(fncall)    \
  do {                          \
    if ((fncall) != 0) abort(); \
  } while (0)

void SPVM_MUTEX_init(void* mutex) {
  
  SAFE_PTHREAD(pthread_rwlock_init((pthread_rwlock_t*)mutex, NULL));
}

void SPVM_MUTEX_destroy(void* mutex) {
  SAFE_PTHREAD(pthread_rwlock_destroy((pthread_rwlock_t*)mutex));
}

void SPVM_MUTEX_lock (void* mutex) {
  SAFE_PTHREAD(pthread_rwlock_wrlock((pthread_rwlock_t*)mutex));
}

void SPVM_MUTEX_unlock (void* mutex) {
  SAFE_PTHREAD(pthread_rwlock_unlock((pthread_rwlock_t*)mutex));
}

void SPVM_MUTEX_reader_lock (void* mutex) {
  SAFE_PTHREAD(pthread_rwlock_rdlock((pthread_rwlock_t*)mutex));
}

void SPVM_MUTEX_reader_unlock (void* mutex) {
  SAFE_PTHREAD(pthread_rwlock_unlock((pthread_rwlock_t*)mutex));
}

int32_t SPVM_MUTEX_size () {
  return sizeof(pthread_rwlock_t);
}

#endif
