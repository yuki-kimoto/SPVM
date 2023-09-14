// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_mutex.h"
#include "spvm_allocator.h"

#if defined(_WIN32)

#include <windows.h>

SPVM_MUTEX* SPVM_MUTEX_new(SPVM_ALLOCATOR* allocator, SPVM_MUTEX* mutex) {
  
  SRWLOCK* lock = (SRWLOCK*)SPVM_ALLOCATOR_alloc_memory_block_tmp(allocator, sizeof(SRWLOCK));
  
  InitializeSRWLock(lock);
  
  mutex->lock = lock;
  
  return mutex;
}

void SPVM_MUTEX_free(SPVM_ALLOCATOR* allocator, SPVM_MUTEX* mutex) {
  
  SRWLOCK* lock = mutex->lock;
  
  SPVM_ALLOCATOR_free_memory_block_tmp(allocator, lock);
}

void SPVM_MUTEX_lock(SPVM_ALLOCATOR* allocator, SPVM_MUTEX* mutex) {
  AcquireSRWLockExclusive((SRWLOCK*)mutex->lock);
}

void SPVM_MUTEX_unlock(SPVM_ALLOCATOR* allocator, SPVM_MUTEX* mutex) {
  ReleaseSRWLockExclusive((SRWLOCK*)mutex->lock);
}

void SPVM_MUTEX_reader_lock(SPVM_ALLOCATOR* allocator, SPVM_MUTEX* mutex) {
  AcquireSRWLockShared((SRWLOCK*)mutex->lock);
}

void SPVM_MUTEX_reader_unlock(SPVM_ALLOCATOR* allocator, SPVM_MUTEX* mutex) {
  ReleaseSRWLockShared((SRWLOCK*)mutex->lock);
}

#else

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define SAFE_PTHREAD(fncall)    \
  do {                          \
    if ((fncall) != 0) abort(); \
  } while (0)

SPVM_MUTEX* SPVM_MUTEX_new(SPVM_ALLOCATOR* allocator, SPVM_MUTEX* mutex) {
  
  pthread_rwlock_t* lock = (pthread_rwlock_t*)SPVM_ALLOCATOR_alloc_memory_block_tmp(allocator, sizeof(pthread_rwlock_t));
  
  SAFE_PTHREAD(pthread_rwlock_init((pthread_rwlock_t*)mutex->lock, NULL));
  
  mutex->lock = lock;
  
  return mutex;
}

void SPVM_MUTEX_free(SPVM_ALLOCATOR* allocator, SPVM_MUTEX* mutex) {
  
  pthread_rwlock_t* lock = mutex->lock;
  
  SAFE_PTHREAD(pthread_rwlock_destroy((pthread_rwlock_t*)mutex->lock));
  
  SPVM_ALLOCATOR_free_memory_block_tmp(allocator, lock);
}

void SPVM_MUTEX_lock(SPVM_ALLOCATOR* allocator, SPVM_MUTEX* mutex) {
  SAFE_PTHREAD(pthread_rwlock_wrlock((pthread_rwlock_t*)mutex->lock));
}

void SPVM_MUTEX_unlock(SPVM_ALLOCATOR* allocator, SPVM_MUTEX* mutex) {
  SAFE_PTHREAD(pthread_rwlock_unlock((pthread_rwlock_t*)mutex->lock));
}

void SPVM_MUTEX_reader_lock(SPVM_ALLOCATOR* allocator, SPVM_MUTEX* mutex) {
  SAFE_PTHREAD(pthread_rwlock_rdlock((pthread_rwlock_t*)mutex->lock));
}

void SPVM_MUTEX_reader_unlock(SPVM_ALLOCATOR* allocator, SPVM_MUTEX* mutex) {
  SAFE_PTHREAD(pthread_rwlock_unlock((pthread_rwlock_t*)mutex->lock));
}

#endif
