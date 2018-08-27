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

#endif
