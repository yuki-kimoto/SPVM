// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_OBJECT_H
#define SPVM_OBJECT_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

// SPVM_OBJECT
struct spvm_object {
  void* pointer;
  SPVM_WEAKEN_BACKREF* weaken_backref_head;
  SPVM_RUNTIME_BASIC_TYPE* basic_type;
  int32_t ref_count;
  uint8_t type_dimension;
  uint8_t flag;
  int32_t length;
};

enum {
  SPVM_OBJECT_C_FLAG_IS_READ_ONLY = 1,
};

#endif
