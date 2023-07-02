// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_DUMPER_H
#define SPVM_DUMPER_H

#include "spvm_typedecl.h"

void SPVM_DUMPER_dump_constant(SPVM_COMPILER* compiler, SPVM_CONSTANT* constant);
void SPVM_DUMPER_dump_field(SPVM_COMPILER* compiler, SPVM_FIELD* field);
void SPVM_DUMPER_dump_method(SPVM_COMPILER* compiler, SPVM_METHOD* method);
void SPVM_DUMPER_dump_method_opcode_list(SPVM_COMPILER* compiler, SPVM_METHOD* method);
void SPVM_DUMPER_dump_var_decl(SPVM_COMPILER* compiler, SPVM_VAR_DECL* var_decl);
void SPVM_DUMPER_dump_basic_types(SPVM_COMPILER* compiler, SPVM_LIST* basic_types);
void SPVM_DUMPER_dump_basic_types_opcode_list(SPVM_COMPILER* compiler, SPVM_LIST* basic_types);
void SPVM_DUMPER_dump_ast(SPVM_COMPILER* compiler, SPVM_OP* op);
void SPVM_DUMPER_dump_opcode_list(SPVM_COMPILER* compiler, SPVM_OPCODE_LIST* opcode_list);

#endif
