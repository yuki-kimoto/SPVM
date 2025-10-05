// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_OBJECT_H
#define SPVM_OBJECT_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

// SPVM_OBJECT
// Note: volatile is for atomic operation
struct spvm_object {
  void* pointer;
  SPVM_WEAKEN_BACKREF* weaken_backref_head;
  SPVM_RUNTIME_BASIC_TYPE* basic_type;
  volatile int32_t ref_count;
  uint8_t type_dimension;
  volatile uint8_t flag;
  int32_t length;
  void* data;
};

enum {
  SPVM_OBJECT_C_FLAG_IS_READ_ONLY = 1,
  SPVM_OBJECT_C_FLAG_NO_FREE = 2,
  SPVM_OBJECT_C_FLAG_IS_OPTIONS = 4,
};

#endif
