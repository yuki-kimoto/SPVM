// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_CALL_METHOD_H
#define SPVM_CALL_METHOD_H

#include "spvm_typedecl.h"

struct spvm_call_method {
  SPVM_OP* op_name;
  SPVM_METHOD* method;
  const char* basic_type_name;
  int32_t args_length;
  int8_t is_class_method_call;
  int8_t call_super;
  int8_t is_static_instance_method_call;
  int8_t is_current_class;
};

SPVM_CALL_METHOD* SPVM_CALL_METHOD_new(SPVM_COMPILER* compiler);

#endif
