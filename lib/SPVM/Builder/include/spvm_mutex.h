// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_MUTEX_H
#define SPVM_MUTEX_H

#include "spvm_typedecl.h"

struct spvm_mutex;
typedef struct spvm_mutex SPVM_MUTEX;

struct spvm_mutex {
   void* lock;
   SPVM_ALLOCATOR* allocator;
};

SPVM_MUTEX* SPVM_MUTEX_new (SPVM_ALLOCATOR* allocator);

void SPVM_MUTEX_free (SPVM_MUTEX* mutex);

void SPVM_MUTEX_lock (SPVM_MUTEX* mutex);

void SPVM_MUTEX_unlock (SPVM_MUTEX* mutex);

void SPVM_MUTEX_reader_lock (SPVM_MUTEX* mutex);

void SPVM_MUTEX_reader_unlock (SPVM_MUTEX* mutex);

#endif  // SPVM_MUTEX_H
