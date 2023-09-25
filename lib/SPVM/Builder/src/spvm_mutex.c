// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_mutex.h"
#include "spvm_allocator.h"

#if defined(_WIN32)

#include <windows.h>

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
