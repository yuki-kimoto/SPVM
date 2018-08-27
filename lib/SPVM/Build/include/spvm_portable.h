#ifndef SPVM_PORTABLE_H
#define SPVM_PORTABLE_H

#include "spvm_base.h"

// Field information
struct SPVM_portable {
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

  int32_t types_unit;
  int32_t types_capacity;
  int32_t types_length;
  int32_t* types;
};

SPVM_PORTABLE* SPVM_PORTABLE_new();

int32_t SPVM_PORTABLE_push_runtime_string(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, const char* string);
void SPVM_PORTABLE_push_portable_arg(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_MY* my);
void SPVM_PORTABLE_push_portable_basic_type(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_BASIC_TYPE* basic_type);
void SPVM_PORTABLE_push_portable_field(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_FIELD* field);
void SPVM_PORTABLE_push_portable_package_var(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_PACKAGE_VAR* package_var);
void SPVM_PORTABLE_push_portable_sub(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_SUB* sub);
void SPVM_PORTABLE_push_portable_package(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_PACKAGE* package);

#endif
