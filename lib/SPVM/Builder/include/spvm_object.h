// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_OBJECT_H
#define SPVM_OBJECT_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

// SPVM_OBJECT
struct spvm_object {
  SPVM_WEAKEN_BACKREF* weaken_backref_head;
  void* pointer;
  int32_t ref_count;
  int32_t basic_type_id;
  uint8_t type_dimension;
  uint8_t flag;
  int32_t length;
};

enum {
  SPVM_OBJECT_C_FLAG_HAS_DESTRUCTOR = 1,
  SPVM_OBJECT_C_FLAG_IS_READ_ONLY = 2,
  SPVM_OBJECT_C_FLAG_POINTER_NO_NEED_FREE = 4,
};

#endif
