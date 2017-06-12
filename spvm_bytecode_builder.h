#ifndef SPVM_BYTECODE_BUILDER_H
#define SPVM_BYTECODE_BUILDER_H

#include "spvm_base.h"

void SPVM_BYTECODE_BUILDER_build_bytecode_array(SPVM_* spvm);
void SPVM_BYTECODE_BUILDER_push_load_bytecode(SPVM_* spvm, SPVM_BYTECODE_ARRAY* bytecode_array, SPVM_OP* op_var);
void SPVM_BYTECODE_BUILDER_push_inc_bytecode(SPVM_* spvm, SPVM_BYTECODE_ARRAY* bytecode_array, SPVM_OP* op_inc, int32_t value);

#endif
