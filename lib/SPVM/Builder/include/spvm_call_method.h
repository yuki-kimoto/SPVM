#ifndef SPVM_CALL_METHOD_H
#define SPVM_CALL_METHOD_H

#include "spvm_typedecl.h"

struct spvm_call_method {
  SPVM_OP* op_invocant;
  SPVM_OP* op_name;
  SPVM_METHOD* method;
  int32_t call_type_id;
  int32_t constant_pool_id;
  int8_t is_class_method_call;
};

SPVM_CALL_METHOD* SPVM_CALL_METHOD_new(SPVM_COMPILER* compiler);

#endif
