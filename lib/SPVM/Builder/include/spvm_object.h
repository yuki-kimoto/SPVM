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
  int32_t basic_type_id;
  const char* basic_type_name;
  int32_t ref_count;
  uint8_t type_dimension;
  uint8_t flag;
  int32_t length;
};

enum {
  SPVM_OBJECT_C_FLAG_IS_READ_ONLY = 1,
};

#endif
