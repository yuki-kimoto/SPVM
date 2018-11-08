#ifndef SPVM_PORTABLE_H
#define SPVM_PORTABLE_H

#include "spvm_base.h"

// Field information
struct SPVM_portable {
  char* string_pool;
  int32_t string_pool_length;

  int32_t* constant_pool;
  int32_t constant_pool_length;

  int32_t basic_types_length;
  SPVM_RUNTIME_BASIC_TYPE* basic_types;

  int32_t packages_length;
  SPVM_RUNTIME_PACKAGE* packages;

  int32_t fields_length;
  SPVM_RUNTIME_FIELD* fields;

  int32_t package_vars_length;
  SPVM_RUNTIME_PACKAGE_VAR* package_vars;

  int32_t subs_length;
  SPVM_RUNTIME_SUB* subs;

  int32_t args_length;
  SPVM_RUNTIME_MY* args;

  int32_t info_switch_info_ints_capacity;
  int32_t info_switch_infos_length;
  int32_t info_switch_info_ints_length;
  int32_t* info_switch_info_ints;

  int32_t opcodes_length;
  SPVM_OPCODE* opcodes;
  int8_t is_static;
};

SPVM_PORTABLE* SPVM_PORTABLE_new();
SPVM_PORTABLE* SPVM_PORTABLE_build_portable(SPVM_COMPILER* compiler);

void SPVM_PORTABLE_push_sub(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, SPVM_SUB* sub);
void SPVM_PORTABLE_push_arg(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, SPVM_MY* my);
void SPVM_PORTABLE_push_basic_type(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, SPVM_BASIC_TYPE* basic_type);
void SPVM_PORTABLE_push_field(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, SPVM_FIELD* field);
void SPVM_PORTABLE_push_package_var(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, SPVM_PACKAGE_VAR* package_var);
void SPVM_PORTABLE_push_package(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, SPVM_PACKAGE* package);
void SPVM_PORTABLE_push_info_switch_info(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, SPVM_SWITCH_INFO* info_switch_info);
void SPVM_PORTABLE_free(SPVM_PORTABLE* portable);

#endif
