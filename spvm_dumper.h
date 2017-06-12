#ifndef SPVM_DUMPER_H
#define SPVM_DUMPER_H

#include "spvm_base.h"

void SPVM_DUMPER_dump_spvm(SPVM_* spvm);
void SPVM_DUMPER_dump_classs(SPVM_* spvm, SPVM_ARRAY* classs);
void SPVM_DUMPER_dump_constants(SPVM_* spvm, SPVM_ARRAY* constants);
void SPVM_DUMPER_dump_constant(SPVM_* spvm, SPVM_CONSTANT* constant);
void SPVM_DUMPER_dump_field(SPVM_* spvm, SPVM_FIELD* field);
void SPVM_DUMPER_dump_sub(SPVM_* spvm, SPVM_SUB* sub);
void SPVM_DUMPER_dump_my_var(SPVM_* spvm, SPVM_MY_VAR* my_var);
void SPVM_DUMPER_dump_enumeration_value(SPVM_* spvm, SPVM_ENUMERATION_VALUE* enumeration_value);
void SPVM_DUMPER_dump_packages(SPVM_* spvm, SPVM_ARRAY* packages);
void SPVM_DUMPER_dump_resolved_types(SPVM_* spvm, SPVM_ARRAY* resolved_types);
void SPVM_DUMPER_dump_ast(SPVM_* spvm, SPVM_OP* op);
void SPVM_DUMPER_dump_constant_pool(SPVM_* spvm, SPVM_CONSTANT_POOL* constant_pool);
void SPVM_DUMPER_dump_bytecode_array(SPVM_* spvm, SPVM_BYTECODE_ARRAY* bytecode_array, int32_t base, int32_t length);

#endif
