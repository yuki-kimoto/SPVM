#ifndef SPVM_BYTECODE_BUILDER_H
#define SPVM_BYTECODE_BUILDER_H

#include "spvm_base.h"

void SPVM_BYTECODE_BUILDER_build_bytecode_array(SPVM_COMPILER* compiler);
void SPVM_BYTECODE_BUILDER_push_load_bytecode(SPVM_COMPILER* compiler, SPVM_BYTECODE_ARRAY* bytecode_array, SPVM_OP* op_var);
void SPVM_BYTECODE_BUILDER_push_inc_bytecode(SPVM_COMPILER* compiler, SPVM_BYTECODE_ARRAY* bytecode_array, SPVM_OP* op_inc, int32_t value);

#endif
