// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_CLASS_H
#define SPVM_CLASS_H

#include "spvm_typedecl.h"

struct spvm_class {
  SPVM_TYPE* type;
  const char* parent_class_name;
  SPVM_CLASS* parent_class;
  int32_t fields_size;
  SPVM_OP* op_class;
};

SPVM_CLASS* SPVM_CLASS_new(SPVM_COMPILER* compiler);
const char* const* SPVM_CLASS_C_CATEGORY_NAMES(void);

#endif
