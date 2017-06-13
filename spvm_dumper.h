#ifndef SPVM_DUMPER_H
#define SPVM_DUMPER_H

#include "spvm_base.h"

void SPVM_DUMPER_dump_spvm(SPVM_PARSER* parser);
void SPVM_DUMPER_dump_classs(SPVM_PARSER* parser, SPVM_ARRAY* classs);
void SPVM_DUMPER_dump_constants(SPVM_PARSER* parser, SPVM_ARRAY* constants);
void SPVM_DUMPER_dump_constant(SPVM_PARSER* parser, SPVM_CONSTANT* constant);
void SPVM_DUMPER_dump_field(SPVM_PARSER* parser, SPVM_FIELD* field);
void SPVM_DUMPER_dump_sub(SPVM_PARSER* parser, SPVM_SUB* sub);
void SPVM_DUMPER_dump_my_var(SPVM_PARSER* parser, SPVM_MY_VAR* my_var);
void SPVM_DUMPER_dump_enumeration_value(SPVM_PARSER* parser, SPVM_ENUMERATION_VALUE* enumeration_value);
void SPVM_DUMPER_dump_packages(SPVM_PARSER* parser, SPVM_ARRAY* packages);
void SPVM_DUMPER_dump_resolved_types(SPVM_PARSER* parser, SPVM_ARRAY* resolved_types);
void SPVM_DUMPER_dump_ast(SPVM_PARSER* parser, SPVM_OP* op);
void SPVM_DUMPER_dump_constant_pool(SPVM_PARSER* parser, SPVM_CONSTANT_POOL* constant_pool);
void SPVM_DUMPER_dump_bytecode_array(SPVM_PARSER* parser, SPVM_BYTECODE_ARRAY* bytecode_array, int32_t base, int32_t length);

#endif
