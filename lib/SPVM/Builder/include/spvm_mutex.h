// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_MUTEX_H
#define SPVM_MUTEX_H

#include "spvm_typedecl.h"

#if defined(_WIN32)

#include <windows.h>

void SPVM_MUTEX_lock (SRWLOCK* mutex);

void SPVM_MUTEX_unlock (SRWLOCK* mutex);

void SPVM_MUTEX_reader_lock (SRWLOCK* mutex);

void SPVM_MUTEX_reader_unlock (SRWLOCK* mutex);

int32_t SPVM_MUTEX_size ();

#else

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define SAFE_PTHREAD(fncall)    \
  do {                          \
    if ((fncall) != 0) abort(); \
  } while (0)

void SPVM_MUTEX_lock (pthread_rwlock_t* mutex);

void SPVM_MUTEX_unlock (pthread_rwlock_t* mutex);

void SPVM_MUTEX_reader_lock (pthread_rwlock_t* mutex);

void SPVM_MUTEX_reader_unlock (pthread_rwlock_t* mutex);

int32_t SPVM_MUTEX_size ();

#endif // defined(_WIN32)

#endif // SPVM_MUTEX_H
