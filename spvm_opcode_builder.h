#ifndef SPVM_BYTECODE_BUILDER_H
#define SPVM_BYTECODE_BUILDER_H

#include "spvm_base.h"

void SPVM_BYTECODE_BUILDER_build_bytecode_array(SPVM_COMPILER* compiler);
void SPVM_BYTECODE_BUILDER_push_inc_opcode(SPVM_COMPILER* compiler, SPVM_OPCODE_ARRAY* opcode_array, SPVM_OP* op_inc, int32_t value);

#endif
