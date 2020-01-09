#ifndef SPVM_RUNTIME_INFO_H
#define SPVM_RUNTIME_INFO_H

#include "spvm_base.h"

struct SPVM_runtime_info {
  char* memory_pool;
  
  SPVM_OPCODE* opcodes;
  int32_t opcodes_length;

  SPVM_RUNTIME_BASIC_TYPE* basic_types;
  int32_t basic_types_length;

  SPVM_RUNTIME_PACKAGE* packages;
  int32_t packages_length;

  SPVM_RUNTIME_PACKAGE_VAR* package_vars;
  int32_t package_vars_length;

  SPVM_RUNTIME_FIELD* fields;
  int32_t fields_length;

  SPVM_RUNTIME_SUB* subs;
  int32_t subs_length;

  SPVM_RUNTIME_ARG* args;
  int32_t args_length;

  int32_t* constant_pool;
  int32_t constant_pool_length;

  char* string_pool;
  int32_t string_pool_length;

  int8_t is_static;
};

SPVM_RUNTIME_INFO* SPVM_RUNTIME_INFO_new();
SPVM_RUNTIME_INFO* SPVM_RUNTIME_INFO_build_runtime_info(SPVM_COMPILER* compiler);

void SPVM_RUNTIME_INFO_push_package(SPVM_COMPILER* compiler, SPVM_RUNTIME_INFO* runtime_info, SPVM_PACKAGE* package);
void SPVM_RUNTIME_INFO_push_sub(SPVM_COMPILER* compiler, SPVM_RUNTIME_INFO* runtime_info, SPVM_SUB* sub);
void SPVM_RUNTIME_INFO_push_arg(SPVM_COMPILER* compiler, SPVM_RUNTIME_INFO* runtime_info, SPVM_MY* my);
void SPVM_RUNTIME_INFO_push_basic_type(SPVM_COMPILER* compiler, SPVM_RUNTIME_INFO* runtime_info, SPVM_BASIC_TYPE* basic_type);
void SPVM_RUNTIME_INFO_push_field(SPVM_COMPILER* compiler, SPVM_RUNTIME_INFO* runtime_info, SPVM_FIELD* field);
void SPVM_RUNTIME_INFO_push_package_var(SPVM_COMPILER* compiler, SPVM_RUNTIME_INFO* runtime_info, SPVM_PACKAGE_VAR* package_var);
void SPVM_RUNTIME_INFO_free(SPVM_RUNTIME_INFO* runtime_info);

#endif
