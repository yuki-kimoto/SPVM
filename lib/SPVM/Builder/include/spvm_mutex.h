// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_MUTEX_H
#define SPVM_MUTEX_H

#include "spvm_typedecl.h"

void SPVM_MUTEX_init(void* mutex);

void SPVM_MUTEX_destroy(void* mutex);

void SPVM_MUTEX_lock (void* mutex);

void SPVM_MUTEX_unlock (void* mutex);

void SPVM_MUTEX_reader_lock (void* mutex);

void SPVM_MUTEX_reader_unlock (void* mutex);

int32_t SPVM_MUTEX_size ();

#endif  // SPVM_MUTEX_H
