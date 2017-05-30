#ifndef SPVM_DUMPER_H
#define SPVM_DUMPER_H

#include "spvm_base.h"

void SPVM_DUMPER_dump_spvm(SPVM* spvm);
void SPVM_DUMPER_dump_classs(SPVM* spvm, SPVM_ARRAY* classs);
void SPVM_DUMPER_dump_constants(SPVM* spvm, SPVM_ARRAY* constants);
void SPVM_DUMPER_dump_constant(SPVM* spvm, SPVM_CONSTANT* constant);
void SPVM_DUMPER_dump_field(SPVM* spvm, SPVM_FIELD* field);
void SPVM_DUMPER_dump_sub(SPVM* spvm, SPVM_SUB* sub);
void SPVM_DUMPER_dump_my_var(SPVM* spvm, SPVM_MY_VAR* my_var);
void SPVM_DUMPER_dump_enumeration_value(SPVM* spvm, SPVM_ENUMERATION_VALUE* enumeration_value);
void SPVM_DUMPER_dump_packages(SPVM* spvm, SPVM_ARRAY* packages);
void SPVM_DUMPER_dump_resolved_types(SPVM* spvm, SPVM_ARRAY* resolved_types);
void SPVM_DUMPER_dump_ast(SPVM* spvm, SPVM_OP* op);
void SPVM_DUMPER_dump_constant_pool(SPVM* spvm, SPVM_CONSTANT_POOL* constant_pool);
void SPVM_DUMPER_dump_bytecode_array(SPVM* spvm, SPVM_BYTECODE_ARRAY* bytecode_array, int32_t base, int32_t length);

#endif
