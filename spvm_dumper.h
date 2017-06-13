#ifndef SPVM_DUMPER_H
#define SPVM_DUMPER_H

#include "spvm_base.h"

void SPVM_DUMPER_dump_spvm(SPVM_COMPILER* compiler);
void SPVM_DUMPER_dump_classs(SPVM_COMPILER* compiler, SPVM_ARRAY* classs);
void SPVM_DUMPER_dump_constants(SPVM_COMPILER* compiler, SPVM_ARRAY* constants);
void SPVM_DUMPER_dump_constant(SPVM_COMPILER* compiler, SPVM_CONSTANT* constant);
void SPVM_DUMPER_dump_field(SPVM_COMPILER* compiler, SPVM_FIELD* field);
void SPVM_DUMPER_dump_sub(SPVM_COMPILER* compiler, SPVM_SUB* sub);
void SPVM_DUMPER_dump_my_var(SPVM_COMPILER* compiler, SPVM_MY_VAR* my_var);
void SPVM_DUMPER_dump_enumeration_value(SPVM_COMPILER* compiler, SPVM_ENUMERATION_VALUE* enumeration_value);
void SPVM_DUMPER_dump_packages(SPVM_COMPILER* compiler, SPVM_ARRAY* packages);
void SPVM_DUMPER_dump_resolved_types(SPVM_COMPILER* compiler, SPVM_ARRAY* resolved_types);
void SPVM_DUMPER_dump_ast(SPVM_COMPILER* compiler, SPVM_OP* op);
void SPVM_DUMPER_dump_constant_pool(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool);
void SPVM_DUMPER_dump_bytecode_array(SPVM_COMPILER* compiler, SPVM_BYTECODE_ARRAY* bytecode_array, int32_t base, int32_t length);

#endif
