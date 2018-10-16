#ifndef SPVM_PORTABLE_H
#define SPVM_PORTABLE_H

#include "spvm_base.h"

// Field information
struct SPVM_portable {
  char** symbols;
  int32_t symbols_capacity;
  int32_t symbols_length;

  int32_t basic_types_length;
  SPVM_RUNTIME_BASIC_TYPE* basic_types;

  int32_t packages_capacity;
  int32_t packages_length;
  SPVM_RUNTIME_PACKAGE* packages;

  int32_t fields_capacity;
  int32_t fields_length;
  SPVM_RUNTIME_FIELD* fields;

  int32_t package_vars_capacity;
  int32_t package_vars_length;
  SPVM_RUNTIME_PACKAGE_VAR* package_vars;

  int32_t subs_unit;
  int32_t subs_capacity;
  int32_t subs_length;
  int32_t* subs;

  int32_t args_capacity;
  int32_t args_length;
  SPVM_RUNTIME_MY* args;

  int32_t mys_capacity;
  int32_t mys_length;
  SPVM_RUNTIME_MY* mys;

  int32_t info_package_var_ids_capacity;
  int32_t info_package_var_ids_length;
  int32_t* info_package_var_ids;

  int32_t info_sub_ids_capacity;
  int32_t info_sub_ids_length;
  int32_t* info_sub_ids;

  int32_t info_field_ids_capacity;
  int32_t info_field_ids_length;
  int32_t* info_field_ids;
  
  int32_t info_types_capacity;
  int32_t info_types_length;
  SPVM_RUNTIME_INFO_TYPE* info_types;

  int32_t info_switch_info_ints_capacity;
  int32_t info_switch_infos_length;
  int32_t info_switch_info_ints_length;
  int32_t* info_switch_info_ints;

  int32_t info_long_values_capacity;
  int64_t* info_long_values;
  int32_t info_long_values_length;

  int32_t info_double_values_capacity;
  double* info_double_values;
  int32_t info_double_values_length;

  int32_t info_string_values_capacity;
  char** info_string_values;
  int32_t info_string_values_length;

  int32_t info_string_lengths_capacity;
  int32_t* info_string_lengths;
  int32_t info_string_lengths_length;

  int32_t opcodes_length;
  SPVM_OPCODE* opcodes;
  int8_t is_static;
};

SPVM_PORTABLE* SPVM_PORTABLE_new();
void SPVM_PORTABLE_push_sub(SPVM_PORTABLE* portable, SPVM_SUB* sub);
SPVM_PORTABLE* SPVM_PORTABLE_build_portable(SPVM_COMPILER* compiler);
int32_t SPVM_PORTABLE_push_symbol(SPVM_PORTABLE* portable, const char* string);
void SPVM_PORTABLE_push_arg(SPVM_PORTABLE* portable, SPVM_MY* my);
void SPVM_PORTABLE_push_my(SPVM_PORTABLE* portable, SPVM_MY* my);
void SPVM_PORTABLE_push_info_type(SPVM_PORTABLE* portable, SPVM_TYPE* info_type);
void SPVM_PORTABLE_push_info_switch_info(SPVM_PORTABLE* portable, SPVM_SWITCH_INFO* info_switch_info);
void SPVM_PORTABLE_push_info_package_var_id(SPVM_PORTABLE* portable, int32_t info_package_var_id);
void SPVM_PORTABLE_push_info_field_id(SPVM_PORTABLE* portable, int32_t info_field_id);
void SPVM_PORTABLE_push_info_sub_id(SPVM_PORTABLE* portable, int32_t info_sub_id);
void SPVM_PORTABLE_push_info_long_value(SPVM_PORTABLE* portable, int64_t info_long_value);
void SPVM_PORTABLE_push_info_double_value(SPVM_PORTABLE* portable, double info_double_value);
void SPVM_PORTABLE_push_info_string_value(SPVM_PORTABLE* portable, const char* info_string_value, int32_t string_length);
void SPVM_PORTABLE_push_info_string_length(SPVM_PORTABLE* portable, int32_t info_string_length);
void SPVM_PORTABLE_push_basic_type(SPVM_PORTABLE* portable, SPVM_BASIC_TYPE* basic_type);
void SPVM_PORTABLE_push_field(SPVM_PORTABLE* portable, SPVM_FIELD* field);
void SPVM_PORTABLE_push_package_var(SPVM_PORTABLE* portable, SPVM_PACKAGE_VAR* package_var);
void SPVM_PORTABLE_push_package(SPVM_PORTABLE* portable, SPVM_PACKAGE* package);
void SPVM_PORTABLE_free(SPVM_PORTABLE* portable);

#endif
