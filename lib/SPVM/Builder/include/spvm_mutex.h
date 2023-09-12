// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_MUTEX_H
#define SPVM_MUTEX_H

#include "spvm_typedecl.h"

struct spvm_mutex;
typedef struct spvm_mutex SPVM_MUTEX;

struct spvm_mutex {
   void* mutex;
};

#endif  // SPVM_MUTEX_H
