#ifndef SPVM_PORTABLE_H
#define SPVM_PORTABLE_H

#include "spvm_base.h"

// Field information
struct SPVM_portable {
  char** symbols;
  int32_t symbols_capacity;
  int32_t symbols_length;

  int32_t basic_types_unit;
  int32_t basic_types_capacity;
  int32_t basic_types_length;
  int32_t* basic_types;

  int32_t packages_unit;
  int32_t packages_capacity;
  int32_t packages_length;
  int32_t* packages;

  int32_t fields_unit;
  int32_t fields_capacity;
  int32_t fields_length;
  int32_t* fields;

  int32_t package_vars_unit;
  int32_t package_vars_capacity;
  int32_t package_vars_length;
  int32_t* package_vars;

  int32_t subs_unit;
  int32_t subs_capacity;
  int32_t subs_length;
  int32_t* subs;

  int32_t args_unit;
  int32_t args_capacity;
  int32_t args_length;
  int32_t* args;

  int32_t info_package_var_ids_unit;
  int32_t info_package_var_ids_capacity;
  int32_t info_package_var_ids_length;
  int32_t* info_package_var_ids;

  int32_t info_sub_ids_unit;
  int32_t info_sub_ids_capacity;
  int32_t info_sub_ids_length;
  int32_t* info_sub_ids;

  int32_t info_field_ids_unit;
  int32_t info_field_ids_capacity;
  int32_t info_field_ids_length;
  int32_t* info_field_ids;
  
  int32_t info_types_unit;
  int32_t info_types_capacity;
  int32_t info_types_length;
  int32_t* info_types;

  int32_t info_constants_unit;
  int32_t info_constants_capacity;
  int32_t info_constants_length;
  int32_t* info_constants;

  int32_t info_switch_info_ints_capacity;
  int32_t info_switch_infos_length;
  int32_t info_switch_info_ints_length;
  int32_t* info_switch_info_ints;

  int64_t* info_longs;
  int32_t info_longs_length;

  int32_t opcodes_length;
  int64_t* opcodes;
};

SPVM_PORTABLE* SPVM_PORTABLE_new();

int32_t SPVM_PORTABLE_push_runtime_string(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, const char* string);
void SPVM_PORTABLE_push_portable_arg(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_MY* my);
void SPVM_PORTABLE_push_portable_basic_type(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_BASIC_TYPE* basic_type);
void SPVM_PORTABLE_push_portable_field(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_FIELD* field);
void SPVM_PORTABLE_push_portable_package_var(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_PACKAGE_VAR* package_var);
void SPVM_PORTABLE_push_portable_sub(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_SUB* sub);
void SPVM_PORTABLE_push_portable_package(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_PACKAGE* package);
void SPVM_PORTABLE_push_portable_info_type(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_TYPE* info_type);

#endif
