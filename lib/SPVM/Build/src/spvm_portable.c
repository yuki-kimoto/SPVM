#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_portable.h"

#include "spvm_compiler.h"
#include "spvm_type.h"
#include "spvm_package.h"
#include "spvm_type.h"
#include "spvm_op.h"
#include "spvm_hash.h"
#include "spvm_list.h"
#include "spvm_util_allocator.h"
#include "spvm_compiler_allocator.h"
#include "spvm_yacc_util.h"
#include "spvm_list.h"
#include "spvm_opcode_array.h"
#include "spvm_sub.h"
#include "spvm_sub.h"
#include "spvm_field.h"
#include "spvm_package_var.h"
#include "spvm_native.h"
#include "spvm_opcode.h"
#include "spvm_basic_type.h"
#include "spvm_use.h"
#include "spvm_op_checker.h"
#include "spvm_opcode_builder.h"
#include "spvm_object.h"
#include "spvm_my.h"


SPVM_PORTABLE* SPVM_PORTABLE_new() {
  SPVM_PORTABLE* portable = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_PORTABLE));

  portable->strings_capacity = 32;
  
  portable->strings = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * portable->strings_capacity);
  
  return portable;
}

SPVM_PORTABLE* SPVM_PORTABLE_build_portable(SPVM_COMPILER* compiler) {
  
  SPVM_PORTABLE* portable = SPVM_PORTABLE_new();
  
  // Portable basic type
  portable->basic_types_capacity = 8;
  portable->basic_types_unit = 4;
  portable->basic_types = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->basic_types_unit * portable->basic_types_capacity);
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    SPVM_PORTABLE_push_basic_type(portable, basic_type);
  }
  
  // Portable fields
  portable->fields_capacity = 8;
  portable->fields_unit = 10;
  portable->fields = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->fields_unit * portable->fields_capacity);
  for (int32_t field_id = 0; field_id < compiler->fields->length; field_id++) {
    SPVM_BASIC_TYPE* field = SPVM_LIST_fetch(compiler->fields, field_id);
    SPVM_PORTABLE_push_field(portable, field);
  }
  
  // Portable package_vars
  portable->package_vars_capacity = 8;
  portable->package_vars_unit = 8;
  portable->package_vars = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->package_vars_unit * portable->package_vars_capacity);
  for (int32_t package_var_id = 0; package_var_id < compiler->package_vars->length; package_var_id++) {
    SPVM_BASIC_TYPE* package_var = SPVM_LIST_fetch(compiler->package_vars, package_var_id);
    SPVM_PORTABLE_push_package_var(portable, package_var);
  }
  
  
  // Portable args
  portable->args_capacity = 8;
  portable->args_unit = 4;
  portable->args = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->args_unit * portable->args_capacity);

  // Portable info package var ids
  portable->info_package_var_ids_capacity = 8;
  portable->info_package_var_ids_unit = 1;
  portable->info_package_var_ids = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->info_package_var_ids_unit * portable->info_package_var_ids_capacity);

  // Portable info field  ids
  portable->info_field_ids_capacity = 8;
  portable->info_field_ids_unit = 1;
  portable->info_field_ids = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->info_field_ids_unit * portable->info_field_ids_capacity);

  // Portable info sub ids
  portable->info_sub_ids_capacity = 8;
  portable->info_sub_ids_unit = 1;
  portable->info_sub_ids = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->info_sub_ids_unit * portable->info_sub_ids_capacity);

  // Portable subs
  portable->subs_capacity = 8;
  portable->subs_unit = 17;
  portable->subs = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->subs_unit * portable->subs_capacity);
  for (int32_t sub_id = 0; sub_id < compiler->subs->length; sub_id++) {
    SPVM_BASIC_TYPE* sub = SPVM_LIST_fetch(compiler->subs, sub_id);
    SPVM_PORTABLE_push_sub(portable, sub);
  }
  
  // Portable packages
  portable->packages_capacity = 8;
  portable->packages_unit = 4;
  portable->packages = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->packages_unit * portable->packages_capacity);
  for (int32_t package_id = 0; package_id < compiler->packages->length; package_id++) {
    SPVM_BASIC_TYPE* package = SPVM_LIST_fetch(compiler->packages, package_id);
    SPVM_PORTABLE_push_package(portable, package);
  }
  
  return portable;
}

int32_t SPVM_PORTABLE_push_string(SPVM_PORTABLE* portable, const char* string) {
  
  int32_t id = portable->strings_length;
  if (portable->strings_length >= portable->strings_capacity) {
    int32_t new_strings_capacity = portable->strings_capacity * 2;
    char** new_strings = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * new_strings_capacity);
    memcpy(new_strings, portable->strings, sizeof(char*) * portable->strings_length);
    free(portable->strings);
    portable->strings = new_strings;
    portable->strings_capacity = new_strings_capacity;
  }
  
  int32_t string_length = (int32_t)strlen(string);
  
  char* new_string = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(string_length + 1);
  memcpy(new_string, string, string_length);
  new_string[string_length] = '\0';
  
  portable->strings[portable->strings_length] = new_string;
  portable->strings_length++;
  
  return id;
}

void SPVM_PORTABLE_push_arg(SPVM_PORTABLE* portable, SPVM_MY* my) {

  if (portable->args_length >= portable->args_capacity) {
    int32_t new_portable_args_capacity = portable->args_capacity * 2;
    int32_t* new_portable_args = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->args_unit * new_portable_args_capacity);
    memcpy(new_portable_args, portable->args, sizeof(int32_t) * portable->args_unit * portable->args_length);
    free(portable->args);
    portable->args = new_portable_args;
    portable->args_capacity = new_portable_args_capacity;
  }
  
  int32_t* new_portable_arg = (int32_t*)&portable->args[portable->args_unit * portable->args_length];
  new_portable_arg[0] = my->var_id;
  new_portable_arg[1] = my->type->basic_type->id;
  new_portable_arg[2] = my->type->dimension;
  new_portable_arg[3] = my->type->flag;

  portable->args_length++;
}

void SPVM_PORTABLE_push_info_package_var_id(SPVM_PORTABLE* portable, int32_t info_package_var_id) {

  if (portable->info_package_var_ids_length >= portable->info_package_var_ids_capacity) {
    int32_t new_portable_info_package_var_ids_capacity = portable->info_package_var_ids_capacity * 2;
    int32_t* new_portable_info_package_var_ids = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->info_package_var_ids_unit * new_portable_info_package_var_ids_capacity);
    memcpy(new_portable_info_package_var_ids, portable->info_package_var_ids, sizeof(int32_t) * portable->info_package_var_ids_unit * portable->info_package_var_ids_length);
    free(portable->info_package_var_ids);
    portable->info_package_var_ids = new_portable_info_package_var_ids;
    portable->info_package_var_ids_capacity = new_portable_info_package_var_ids_capacity;
  }
  
  int32_t* new_portable_info_package_var_id = (int32_t*)&portable->info_package_var_ids[portable->info_package_var_ids_unit * portable->info_package_var_ids_length];
  new_portable_info_package_var_id[0] = info_package_var_id;

  portable->info_package_var_ids_length++;
}

void SPVM_PORTABLE_push_basic_type(SPVM_PORTABLE* portable, SPVM_BASIC_TYPE* basic_type) {
  
  if (portable->basic_types_length >= portable->basic_types_capacity) {
    int32_t new_portable_basic_types_capacity = portable->basic_types_capacity * 2;
    int32_t* new_portable_basic_types = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->basic_types_unit * new_portable_basic_types_capacity);
    memcpy(new_portable_basic_types, portable->basic_types, sizeof(int32_t) * portable->basic_types_unit * portable->basic_types_length);
    free(portable->basic_types);
    portable->basic_types = new_portable_basic_types;
    portable->basic_types_capacity = new_portable_basic_types_capacity;
  }
  
  int32_t* new_portable_basic_type = (int32_t*)&portable->basic_types[portable->basic_types_unit * portable->basic_types_length];
  new_portable_basic_type[0] = SPVM_PORTABLE_push_string(portable, basic_type->name);
  new_portable_basic_type[1] = basic_type->id;
  new_portable_basic_type[2] = basic_type->category;
  if (basic_type->package) {
    new_portable_basic_type[3] = basic_type->package->id;
  }
  else {
    new_portable_basic_type[3] = -1;
  }
  portable->basic_types_length++;
}

void SPVM_PORTABLE_push_field(SPVM_PORTABLE* portable, SPVM_FIELD* field) {
  
  if (portable->fields_length >= portable->fields_capacity) {
    int32_t new_portable_fields_capacity = portable->fields_capacity * 2;
    int32_t* new_portable_fields = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->fields_unit * new_portable_fields_capacity);
    memcpy(new_portable_fields, portable->fields, sizeof(int32_t) * portable->fields_unit * portable->fields_length);
    free(portable->fields);
    portable->fields = new_portable_fields;
    portable->fields_capacity = new_portable_fields_capacity;
  }
  
  int32_t* new_portable_field = (int32_t*)&portable->fields[portable->fields_unit * portable->fields_length];

  new_portable_field[0] = field->id;
  new_portable_field[1] = field->index;
  new_portable_field[2] = field->flag;
  new_portable_field[3] = SPVM_PORTABLE_push_string(portable, field->name);
  new_portable_field[4] = SPVM_PORTABLE_push_string(portable, field->abs_name);
  new_portable_field[5] = SPVM_PORTABLE_push_string(portable, field->signature);
  if (field->type->basic_type) {
    new_portable_field[6] = field->type->basic_type->id;
  }
  else {
    new_portable_field[6] = -1;
  }
  new_portable_field[7] = field->type->dimension;
  new_portable_field[8] = field->type->flag;
  if (field->package) {
    new_portable_field[9] = field->package->id;
  }
  else {
    new_portable_field[9] = -1;
  }
  
  portable->fields_length++;
}

void SPVM_PORTABLE_push_package_var(SPVM_PORTABLE* portable, SPVM_PACKAGE_VAR* package_var) {
  
  if (portable->package_vars_length >= portable->package_vars_capacity) {
    int32_t new_portable_package_vars_capacity = portable->package_vars_capacity * 2;
    int32_t* new_portable_package_vars = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->package_vars_unit * new_portable_package_vars_capacity);
    memcpy(new_portable_package_vars, portable->package_vars, sizeof(int32_t) * portable->package_vars_unit * portable->package_vars_length);
    free(portable->package_vars);
    portable->package_vars = new_portable_package_vars;
    portable->package_vars_capacity = new_portable_package_vars_capacity;
  }
  
  int32_t* new_portable_package_var = (int32_t*)&portable->package_vars[portable->package_vars_unit * portable->package_vars_length];

  new_portable_package_var[0] = package_var->id;
  new_portable_package_var[1] = SPVM_PORTABLE_push_string(portable, package_var->name);
  new_portable_package_var[2] = SPVM_PORTABLE_push_string(portable, package_var->abs_name);
  new_portable_package_var[3] = SPVM_PORTABLE_push_string(portable, package_var->signature);
  if (package_var->type->basic_type) {
    new_portable_package_var[4] = package_var->type->basic_type->id;
  }
  else {
    new_portable_package_var[4] = -1;
  }
  new_portable_package_var[5] = package_var->type->dimension;
  new_portable_package_var[6] = package_var->type->flag;
  if (package_var->package) {
    new_portable_package_var[7] = package_var->package->id;
  }
  else {
    new_portable_package_var[7] = -1;
  }
  
  portable->package_vars_length++;
}

void SPVM_PORTABLE_push_sub(SPVM_PORTABLE* portable, SPVM_SUB* sub) {
  
  if (portable->subs_length >= portable->subs_capacity) {
    int32_t new_portable_subs_capacity = portable->subs_capacity * 2;
    int32_t* new_portable_subs = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->subs_unit * new_portable_subs_capacity);
    memcpy(new_portable_subs, portable->subs, sizeof(int32_t) * portable->subs_unit * portable->subs_length);
    free(portable->subs);
    portable->subs = new_portable_subs;
    portable->subs_capacity = new_portable_subs_capacity;
  }
  
  int32_t* new_portable_sub = (int32_t*)&portable->subs[portable->subs_unit * portable->subs_length];

  new_portable_sub[0] = sub->id;
  new_portable_sub[1] = sub->flag;
  new_portable_sub[2] = SPVM_PORTABLE_push_string(portable, sub->name);
  new_portable_sub[3] = SPVM_PORTABLE_push_string(portable, sub->abs_name);
  new_portable_sub[4] = SPVM_PORTABLE_push_string(portable, sub->signature);
  if (sub->package) {
    new_portable_sub[5] = sub->package->id;
  }
  else {
    new_portable_sub[5] = -1;
  }

  new_portable_sub[6] = SPVM_PORTABLE_push_string(portable, sub->file);
  new_portable_sub[7] = sub->line;
  new_portable_sub[8] = sub->args_alloc_length;
  new_portable_sub[9] = sub->vars_alloc_length;

  new_portable_sub[10] = sub->return_type->basic_type->id;
  new_portable_sub[11] = sub->return_type->dimension;
  new_portable_sub[12] = sub->return_type->flag;
  new_portable_sub[13] = sub->opcode_base;
  new_portable_sub[14] = sub->mortal_stack_length;
  new_portable_sub[15] = portable->args_length;
  new_portable_sub[16] = sub->args->length;
  
  SPVM_MY* my = sub->args;
  for (int32_t arg_id = 0; arg_id < sub->args->length; arg_id++) {
    SPVM_MY* my = SPVM_LIST_fetch(sub->args, arg_id);
    SPVM_PORTABLE_push_arg(portable, my);
  }

  portable->subs_length++;
}

void SPVM_PORTABLE_push_package(SPVM_PORTABLE* portable, SPVM_PACKAGE* package) {
  
  if (portable->packages_length >= portable->packages_capacity) {
    int32_t new_portable_packages_capacity = portable->packages_capacity * 2;
    int32_t* new_portable_packages = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->packages_unit * new_portable_packages_capacity);
    memcpy(new_portable_packages, portable->packages, sizeof(int32_t) * portable->packages_unit * portable->packages_length);
    free(portable->packages);
    portable->packages = new_portable_packages;
    portable->packages_capacity = new_portable_packages_capacity;
  }
  
  int32_t* new_portable_package = (int32_t*)&portable->packages[portable->packages_unit * portable->packages_length];

  new_portable_package[0] = package->id;
  new_portable_package[1] = SPVM_PORTABLE_push_string(portable, package->name);
  if (package->sub_destructor) {
    new_portable_package[2] = package->sub_destructor->id;
  }
  else {
    new_portable_package[2] = -1;
  }
  new_portable_package[3] = package->category;
  
  portable->packages_length++;
}

