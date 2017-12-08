#ifndef SPVM_DUMPER_H
#define SPVM_DUMPER_H

#include "spvm_base.h"

void SPVM_DUMPER_dump_all(SPVM_COMPILER* compiler);
void SPVM_DUMPER_dump_classs(SPVM_COMPILER* compiler, SPVM_DYNAMIC_ARRAY* classs);
void SPVM_DUMPER_dump_constants(SPVM_COMPILER* compiler, SPVM_DYNAMIC_ARRAY* constants);
void SPVM_DUMPER_dump_constant(SPVM_COMPILER* compiler, SPVM_CONSTANT* constant);
void SPVM_DUMPER_dump_field(SPVM_COMPILER* compiler, SPVM_FIELD* field);
void SPVM_DUMPER_dump_sub(SPVM_COMPILER* compiler, SPVM_SUB* sub);
void SPVM_DUMPER_dump_subs(SPVM_COMPILER* compiler, SPVM_DYNAMIC_ARRAY* op_subs);
void SPVM_DUMPER_dump_my(SPVM_COMPILER* compiler, SPVM_MY* my);
void SPVM_DUMPER_dump_enumeration_value(SPVM_COMPILER* compiler, SPVM_ENUMERATION_VALUE* enumeration_value);
void SPVM_DUMPER_dump_packages(SPVM_COMPILER* compiler, SPVM_DYNAMIC_ARRAY* packages);
void SPVM_DUMPER_dump_types(SPVM_COMPILER* compiler, SPVM_DYNAMIC_ARRAY* types);
void SPVM_DUMPER_dump_ast(SPVM_COMPILER* compiler, SPVM_OP* op);
void SPVM_DUMPER_dump_constant_pool(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool);
void SPVM_DUMPER_dump_opcode_array(SPVM_COMPILER* compiler, SPVM_OPCODE_ARRAY* opcode_array, int32_t base, int32_t length);

#endif
