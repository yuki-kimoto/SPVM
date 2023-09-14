// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_mutex.h"
#include "spvm_allocator.h"

#if defined(_WIN32)

#include <windows.h>

void SPVM_MUTEX_lock (SRWLOCK* mutex) {
  AcquireSRWLockExclusive(mutex);
}

void SPVM_MUTEX_unlock (SRWLOCK* mutex) {
  ReleaseSRWLockExclusive(mutex);
}

void SPVM_MUTEX_reader_lock (SRWLOCK* mutex) {
  AcquireSRWLockShared(mutex);
}

void SPVM_MUTEX_reader_unlock (SRWLOCK* mutex) {
  ReleaseSRWLockShared(mutex);
}

int32_t SPVM_MUTEX_size () {
  return sizeof(SRWLOCK);
}

#else

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void SPVM_MUTEX_lock (pthread_rwlock_t* mutex) {
  SAFE_PTHREAD(pthread_rwlock_wrlock(mutex));
}

void SPVM_MUTEX_unlock (pthread_rwlock_t* mutex) {
  SAFE_PTHREAD(pthread_rwlock_unlock(mutex));
}

void SPVM_MUTEX_reader_lock (pthread_rwlock_t* mutex) {
  SAFE_PTHREAD(pthread_rwlock_rdlock(mutex));
}

void SPVM_MUTEX_reader_unlock (pthread_rwlock_t* mutex) {
  SAFE_PTHREAD(pthread_rwlock_unlock(mutex));
}

int32_t SPVM_MUTEX_size () {
  return sizeof(pthread_rwlock_t);
}

#endif
