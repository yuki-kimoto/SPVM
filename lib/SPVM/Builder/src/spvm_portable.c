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
#include "spvm_switch_info.h"
#include "spvm_case_info.h"
#include "spvm_constant.h"

#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_package_var.h"
#include "spvm_runtime_my.h"
#include "spvm_runtime_info_type.h"
#include "spvm_runtime_info_switch_info.h"
#include "spvm_runtime_info_case_info.h"

SPVM_PORTABLE* SPVM_PORTABLE_new() {
  SPVM_PORTABLE* portable = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_PORTABLE));

  portable->symbols_capacity = 32;
  
  portable->symbols = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * portable->symbols_capacity);

  portable->fields_capacity = 8;
  portable->fields_unit = 10;
  portable->package_vars_capacity = 8;
  portable->package_vars_unit = 8;
  portable->args_capacity = 8;
  portable->args_unit = 5;
  portable->mys_capacity = 8;
  portable->mys_unit = 5;
  portable->info_package_var_ids_capacity = 8;
  portable->info_package_var_ids_unit = 1;
  portable->info_field_ids_capacity = 8;
  portable->info_field_ids_unit = 1;
  portable->info_sub_ids_capacity = 8;
  portable->info_sub_ids_unit = 1;
  portable->info_types_capacity = 8;
  portable->subs_capacity = 8;
  portable->subs_unit = 44;
  portable->packages_capacity = 8;
  portable->packages_unit = 6;
  
  portable->info_switch_info_ints_capacity = 8;

  portable->info_long_values_capacity = 8;
  portable->info_double_values_capacity = 8;
  portable->info_string_values_capacity = 8;
  portable->info_string_lengths_capacity = 8;
  
  return portable;
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
  new_portable_sub[2] = SPVM_PORTABLE_push_symbol(portable, sub->name);
  new_portable_sub[3] = SPVM_PORTABLE_push_symbol(portable, sub->abs_name);
  new_portable_sub[4] = SPVM_PORTABLE_push_symbol(portable, sub->signature);
  if (sub->package) {
    new_portable_sub[5] = sub->package->id;
  }
  else {
    new_portable_sub[5] = -1;
  }
  
  // Get file base name
  const char* sub_file_base = NULL;
  {
    const char* file = sub->file;

    int32_t file_length = (int32_t)strlen(file);
    int32_t found_sep = 0;
    for (int32_t i = file_length - 1; i >= 0; i--) {
      char ch = file[i];
      if (ch == '/' || ch == '\\') {
        sub_file_base = &file[i + 1];
        found_sep = 1;
        break;
      }
    }
    if (!found_sep) {
      sub_file_base = file;
    }
  }

  new_portable_sub[6] = SPVM_PORTABLE_push_symbol(portable, sub_file_base);
  new_portable_sub[7] = sub->line;
  new_portable_sub[8] = sub->args_alloc_length;
  new_portable_sub[9] = sub->return_type->basic_type->id;
  new_portable_sub[10] = sub->return_type->dimension;
  new_portable_sub[11] = sub->return_type->flag;
  new_portable_sub[12] = sub->opcodes_base;
  new_portable_sub[13] = sub->mortal_stack_length;
  new_portable_sub[14] = portable->args_length;
  new_portable_sub[15] = sub->args->length;
  new_portable_sub[16] = portable->info_package_var_ids_length;
  new_portable_sub[17] = sub->info_package_var_ids->length;
  new_portable_sub[18] = portable->info_field_ids_length;
  new_portable_sub[19] = sub->info_field_ids->length;
  new_portable_sub[20] = portable->info_sub_ids_length;
  new_portable_sub[21] = sub->info_sub_ids->length;
  new_portable_sub[22] = portable->info_types_length;
  new_portable_sub[23] = sub->info_types->length;
  new_portable_sub[24] = portable->info_switch_infos_length;
  new_portable_sub[25] = sub->info_switch_infos->length;
  new_portable_sub[26] = portable->info_long_values_length;
  new_portable_sub[27] = sub->info_long_constants->length;
  new_portable_sub[28] = portable->info_double_values_length;
  new_portable_sub[29] = sub->info_double_constants->length;
  new_portable_sub[30] = portable->info_string_values_length;
  new_portable_sub[31] = sub->info_string_constants->length;
  new_portable_sub[32] = sub->opcodes_length;
  new_portable_sub[33] = portable->mys_length;
  new_portable_sub[34] = sub->mys->length;
  new_portable_sub[35] = sub->call_type_id;
  new_portable_sub[36] = sub->byte_vars_alloc_length;
  new_portable_sub[37] = sub->short_vars_alloc_length;
  new_portable_sub[38] = sub->int_vars_alloc_length;
  new_portable_sub[39] = sub->long_vars_alloc_length;
  new_portable_sub[40] = sub->float_vars_alloc_length;
  new_portable_sub[41] = sub->double_vars_alloc_length;
  new_portable_sub[42] = sub->object_vars_alloc_length;
  new_portable_sub[43] = sub->ref_vars_alloc_length;

  for (int32_t arg_id = 0; arg_id < sub->args->length; arg_id++) {
    SPVM_MY* my = SPVM_LIST_fetch(sub->args, arg_id);
    SPVM_PORTABLE_push_arg(portable, my);
  }
  for (int32_t my_id = 0; my_id < sub->mys->length; my_id++) {
    SPVM_MY* my = SPVM_LIST_fetch(sub->mys, my_id);
    SPVM_PORTABLE_push_my(portable, my);
  }
  

  for (int32_t info_package_var_ids_index = 0; info_package_var_ids_index < sub->info_package_var_ids->length; info_package_var_ids_index++) {
    int32_t info_package_var_id = (intptr_t)SPVM_LIST_fetch(sub->info_package_var_ids, info_package_var_ids_index);
    
    SPVM_PORTABLE_push_info_package_var_id(portable, info_package_var_id);
  }

  for (int32_t info_field_ids_index = 0; info_field_ids_index < sub->info_field_ids->length; info_field_ids_index++) {
    int32_t info_field_id = (intptr_t)SPVM_LIST_fetch(sub->info_field_ids, info_field_ids_index);
    
    SPVM_PORTABLE_push_info_field_id(portable, info_field_id);
  }

  for (int32_t info_sub_ids_index = 0; info_sub_ids_index < sub->info_sub_ids->length; info_sub_ids_index++) {
    int32_t info_sub_id = (intptr_t)SPVM_LIST_fetch(sub->info_sub_ids, info_sub_ids_index);
    
    SPVM_PORTABLE_push_info_sub_id(portable, info_sub_id);
  }

  for (int32_t info_type_id = 0; info_type_id < sub->info_types->length; info_type_id++) {
    SPVM_TYPE* info_type = SPVM_LIST_fetch(sub->info_types, info_type_id);
    SPVM_PORTABLE_push_info_type(portable, info_type);
  }

  for (int32_t info_switch_info_id = 0; info_switch_info_id < sub->info_switch_infos->length; info_switch_info_id++) {
    SPVM_SWITCH_INFO* info_switch_info = SPVM_LIST_fetch(sub->info_switch_infos, info_switch_info_id);
    SPVM_PORTABLE_push_info_switch_info(portable, info_switch_info);
  }

  for (int32_t info_long_values_index = 0; info_long_values_index < sub->info_long_constants->length; info_long_values_index++) {
    SPVM_CONSTANT* constant = SPVM_LIST_fetch(sub->info_long_constants, info_long_values_index);
    SPVM_PORTABLE_push_info_long_value(portable, constant->value.lval);
  }

  for (int32_t info_double_values_index = 0; info_double_values_index < sub->info_double_constants->length; info_double_values_index++) {
    SPVM_CONSTANT* constant = SPVM_LIST_fetch(sub->info_double_constants, info_double_values_index);
    SPVM_PORTABLE_push_info_double_value(portable, constant->value.dval);
  }

  for (int32_t info_string_values_index = 0; info_string_values_index < sub->info_string_constants->length; info_string_values_index++) {
    SPVM_CONSTANT* constant = SPVM_LIST_fetch(sub->info_string_constants, info_string_values_index);
    SPVM_PORTABLE_push_info_string_value(portable, (char*)constant->value.oval, constant->string_length);
  }

  for (int32_t info_string_lengths_index = 0; info_string_lengths_index < sub->info_string_constants->length; info_string_lengths_index++) {
    SPVM_CONSTANT* constant = SPVM_LIST_fetch(sub->info_string_constants, info_string_lengths_index);
    SPVM_PORTABLE_push_info_string_length(portable, constant->string_length);
  }

  portable->subs_length++;
}

SPVM_PORTABLE* SPVM_PORTABLE_build_portable(SPVM_COMPILER* compiler) {
  SPVM_PORTABLE* portable = SPVM_PORTABLE_new();
  
  // Portable basic type
  portable->basic_types = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_BASIC_TYPE) * (compiler->basic_types->length + 1));
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = &portable->basic_types[basic_type_id];
    runtime_basic_type->name_id = SPVM_PORTABLE_push_symbol(portable, basic_type->name);
    runtime_basic_type->id = basic_type->id;
    if (basic_type->package) {
      runtime_basic_type->package_id = basic_type->package->id;
    }
    else {
      runtime_basic_type->package_id = -1;
    }
  }
  portable->basic_types_length = compiler->basic_types->length;
  
  // Portable fields
  portable->fields = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->fields_unit * portable->fields_capacity);
  for (int32_t field_id = 0; field_id < compiler->fields->length; field_id++) {
    SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);
    SPVM_PORTABLE_push_field(portable, field);
  }
  
  // Portable package_vars
  portable->package_vars = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->package_vars_unit * portable->package_vars_capacity);
  for (int32_t package_var_id = 0; package_var_id < compiler->package_vars->length; package_var_id++) {
    SPVM_PACKAGE_VAR* package_var = SPVM_LIST_fetch(compiler->package_vars, package_var_id);
    SPVM_PORTABLE_push_package_var(portable, package_var);
  }
  
  
  // Portable args
  portable->args = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->args_unit * portable->args_capacity);

  // Portable args
  portable->mys = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_MY) * portable->mys_capacity);

  // Portable info_types
  portable->info_types = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_INFO_TYPE) * portable->info_types_capacity);

  // Portable info package var ids
  portable->info_package_var_ids = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->info_package_var_ids_unit * portable->info_package_var_ids_capacity);

  // Portable info field  ids
  portable->info_field_ids = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->info_field_ids_unit * portable->info_field_ids_capacity);

  // Portable info sub ids
  portable->info_sub_ids = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->info_sub_ids_unit * portable->info_sub_ids_capacity);

  // Portable switch info
  portable->info_switch_info_ints = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->info_switch_info_ints_capacity);

  // Portable long values
  portable->info_long_values = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int64_t) * portable->info_long_values_capacity);

  // Portable double values
  portable->info_double_values = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(double) * portable->info_double_values_capacity);

  // Portable string values
  portable->info_string_values = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * portable->info_string_values_capacity);

  portable->info_string_lengths = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->info_string_lengths_capacity);
  
  // Portable subs
  portable->subs = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->subs_unit * portable->subs_capacity);
  for (int32_t sub_id = 0; sub_id < compiler->subs->length; sub_id++) {
    SPVM_SUB* sub = SPVM_LIST_fetch(compiler->subs, sub_id);
    SPVM_PORTABLE_push_sub(portable, sub);
  }
  
  // Portable packages
  portable->packages = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->packages_unit * portable->packages_capacity);
  for (int32_t package_id = 0; package_id < compiler->packages->length; package_id++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_id);
    SPVM_PORTABLE_push_package(portable, package);
  }
  
  // OPCode
  int32_t opcode_length = compiler->opcode_array->length;
  portable->opcodes_length = opcode_length;
  portable->opcodes = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int64_t) * opcode_length);
  memcpy(portable->opcodes, compiler->opcode_array->values, sizeof(int64_t) * opcode_length);
  
  return portable;
}

int32_t SPVM_PORTABLE_push_symbol(SPVM_PORTABLE* portable, const char* string) {
  
  int32_t id = portable->symbols_length;
  if (portable->symbols_length >= portable->symbols_capacity) {
    int32_t new_symbols_capacity = portable->symbols_capacity * 2;
    char** new_symbols = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * new_symbols_capacity);
    memcpy(new_symbols, portable->symbols, sizeof(char*) * portable->symbols_length);
    free(portable->symbols);
    portable->symbols = new_symbols;
    portable->symbols_capacity = new_symbols_capacity;
  }
  
  int32_t string_length = (int32_t)strlen(string);
  
  char* new_string = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(string_length + 1);
  memcpy(new_string, string, string_length);
  new_string[string_length] = '\0';
  
  portable->symbols[portable->symbols_length] = new_string;
  portable->symbols_length++;
  
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
  new_portable_arg[0] = my->type->basic_type->id;
  new_portable_arg[1] = my->type->dimension;
  new_portable_arg[2] = my->type->flag;
  new_portable_arg[3] = my->var_id;
  new_portable_arg[4] = my->value_field_basic_type_id ;

  portable->args_length++;
}

void SPVM_PORTABLE_push_my(SPVM_PORTABLE* portable, SPVM_MY* my) {
  
  if (portable->mys_length >= portable->mys_capacity) {
    int32_t new_portable_mys_capacity = portable->mys_capacity * 2;
    SPVM_RUNTIME_MY* new_portable_mys = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_MY) * new_portable_mys_capacity);
    memcpy(new_portable_mys, portable->mys, sizeof(SPVM_RUNTIME_MY) * portable->mys_length);
    free(portable->mys);
    portable->mys = new_portable_mys;
    portable->mys_capacity = new_portable_mys_capacity;
  }
  
  SPVM_RUNTIME_MY* new_portable_my = &portable->mys[portable->mys_length];
  new_portable_my->basic_type_id = my->type->basic_type->id;
  new_portable_my->type_dimension = my->type->dimension;
  new_portable_my->type_flag = my->type->flag;
  new_portable_my->var_id = my->var_id;
  new_portable_my->value_field_basic_type_id = my->value_field_basic_type_id;
  
  portable->mys_length++;
}

void SPVM_PORTABLE_push_info_type(SPVM_PORTABLE* portable, SPVM_TYPE* info_type) {

  if (portable->info_types_length >= portable->info_types_capacity) {
    int32_t new_portable_info_types_capacity = portable->info_types_capacity * 2;
    SPVM_RUNTIME_INFO_TYPE* new_portable_info_types = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_INFO_TYPE) * new_portable_info_types_capacity);
    memcpy(new_portable_info_types, portable->info_types, sizeof(SPVM_RUNTIME_INFO_TYPE) * portable->info_types_length);
    free(portable->info_types);
    portable->info_types = new_portable_info_types;
    portable->info_types_capacity = new_portable_info_types_capacity;
  }
  
  SPVM_RUNTIME_INFO_TYPE* new_portable_info_type = &portable->info_types[portable->info_types_length];
  new_portable_info_type->basic_type_id = info_type->basic_type->id;
  new_portable_info_type->dimension = info_type->dimension;
  new_portable_info_type->flag = info_type->flag;

  portable->info_types_length++;
}

void SPVM_PORTABLE_push_info_switch_info(SPVM_PORTABLE* portable, SPVM_SWITCH_INFO* info_switch_info) {
  
  SPVM_LIST* case_infos = info_switch_info->cases_ordered;
  int32_t max_extend_length = 1 + case_infos->length * 2;
  
  if (portable->info_switch_info_ints_length + max_extend_length >= portable->info_switch_info_ints_capacity) {
    int32_t new_portable_info_switch_info_ints_capacity = (portable->info_switch_info_ints_capacity + max_extend_length) * 2;
    int32_t* new_portable_info_switch_info_ints = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * new_portable_info_switch_info_ints_capacity);
    memcpy(new_portable_info_switch_info_ints, portable->info_switch_info_ints, sizeof(int32_t) * portable->info_switch_info_ints_length);
    free(portable->info_switch_info_ints);
    portable->info_switch_info_ints = new_portable_info_switch_info_ints;
    portable->info_switch_info_ints_capacity = new_portable_info_switch_info_ints_capacity;
  }
  
  int32_t* new_portable_info_switch_info_ints = (int32_t*)&portable->info_switch_info_ints[portable->info_switch_info_ints_length];
  new_portable_info_switch_info_ints[0] = info_switch_info->default_opcode_rel_index;
  new_portable_info_switch_info_ints[1] = case_infos->length;
  portable->info_switch_info_ints_length += 2;
  
  for (int32_t case_info_index = 0; case_info_index < case_infos->length; case_info_index++) {
    SPVM_CASE_INFO* case_info = SPVM_LIST_fetch(case_infos, case_info_index);
    
    new_portable_info_switch_info_ints[2 + (2 * case_info_index)] = case_info->constant->value.ival;
    new_portable_info_switch_info_ints[2 + (2 * case_info_index) + 1] = case_info->opcode_rel_index;
    portable->info_switch_info_ints_length += 2;
  }
  portable->info_switch_infos_length++;
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

void SPVM_PORTABLE_push_info_field_id(SPVM_PORTABLE* portable, int32_t info_field_id) {

  if (portable->info_field_ids_length >= portable->info_field_ids_capacity) {
    int32_t new_portable_info_field_ids_capacity = portable->info_field_ids_capacity * 2;
    int32_t* new_portable_info_field_ids = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->info_field_ids_unit * new_portable_info_field_ids_capacity);
    memcpy(new_portable_info_field_ids, portable->info_field_ids, sizeof(int32_t) * portable->info_field_ids_unit * portable->info_field_ids_length);
    free(portable->info_field_ids);
    portable->info_field_ids = new_portable_info_field_ids;
    portable->info_field_ids_capacity = new_portable_info_field_ids_capacity;
  }
  
  int32_t* new_portable_info_field_id = (int32_t*)&portable->info_field_ids[portable->info_field_ids_unit * portable->info_field_ids_length];
  new_portable_info_field_id[0] = info_field_id;

  portable->info_field_ids_length++;
}

void SPVM_PORTABLE_push_info_sub_id(SPVM_PORTABLE* portable, int32_t info_sub_id) {

  if (portable->info_sub_ids_length >= portable->info_sub_ids_capacity) {
    int32_t new_portable_info_sub_ids_capacity = portable->info_sub_ids_capacity * 2;
    int32_t* new_portable_info_sub_ids = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->info_sub_ids_unit * new_portable_info_sub_ids_capacity);
    memcpy(new_portable_info_sub_ids, portable->info_sub_ids, sizeof(int32_t) * portable->info_sub_ids_unit * portable->info_sub_ids_length);
    free(portable->info_sub_ids);
    portable->info_sub_ids = new_portable_info_sub_ids;
    portable->info_sub_ids_capacity = new_portable_info_sub_ids_capacity;
  }
  
  int32_t* new_portable_info_sub_id = (int32_t*)&portable->info_sub_ids[portable->info_sub_ids_unit * portable->info_sub_ids_length];
  new_portable_info_sub_id[0] = info_sub_id;

  portable->info_sub_ids_length++;
}

void SPVM_PORTABLE_push_info_long_value(SPVM_PORTABLE* portable, int64_t info_long_value) {

  if (portable->info_long_values_length >= portable->info_long_values_capacity) {
    int32_t new_portable_info_long_values_capacity = portable->info_long_values_capacity * 2;
    int64_t* new_portable_info_long_values = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int64_t) * new_portable_info_long_values_capacity);
    memcpy(new_portable_info_long_values, portable->info_long_values, sizeof(int64_t) * portable->info_long_values_length);
    free(portable->info_long_values);
    portable->info_long_values = new_portable_info_long_values;
    portable->info_long_values_capacity = new_portable_info_long_values_capacity;
  }
  
  portable->info_long_values[portable->info_long_values_length] = info_long_value;

  portable->info_long_values_length++;
}

void SPVM_PORTABLE_push_info_double_value(SPVM_PORTABLE* portable, double info_double_value) {

  if (portable->info_double_values_length >= portable->info_double_values_capacity) {
    int32_t new_portable_info_double_values_capacity = portable->info_double_values_capacity * 2;
    double* new_portable_info_double_values = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(double) * new_portable_info_double_values_capacity);
    memcpy(new_portable_info_double_values, portable->info_double_values, sizeof(int64_t) * portable->info_double_values_length);
    free(portable->info_double_values);
    portable->info_double_values = new_portable_info_double_values;
    portable->info_double_values_capacity = new_portable_info_double_values_capacity;
  }
  
  portable->info_double_values[portable->info_double_values_length] = info_double_value;

  portable->info_double_values_length++;
}

void SPVM_PORTABLE_push_info_string_value(SPVM_PORTABLE* portable, const char* info_string_value, int32_t string_length) {

  if (portable->info_string_values_length >= portable->info_string_values_capacity) {
    int32_t new_portable_info_string_values_capacity = portable->info_string_values_capacity * 2;
    char** new_portable_info_string_values = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * new_portable_info_string_values_capacity);
    memcpy(new_portable_info_string_values, portable->info_string_values, sizeof(char*) * portable->info_string_values_length);
    free(portable->info_string_values);
    portable->info_string_values = new_portable_info_string_values;
    portable->info_string_values_capacity = new_portable_info_string_values_capacity;
  }
  
  portable->info_string_values[portable->info_string_values_length] = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(string_length + 1);
  memcpy(portable->info_string_values[portable->info_string_values_length], info_string_value, string_length);

  portable->info_string_values_length++;
}

void SPVM_PORTABLE_push_info_string_length(SPVM_PORTABLE* portable, int32_t info_string_length) {

  if (portable->info_string_lengths_length >= portable->info_string_lengths_capacity) {
    int32_t new_portable_info_string_lengths_capacity = portable->info_string_lengths_capacity * 2;
    int32_t* new_portable_info_string_lengths = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * new_portable_info_string_lengths_capacity);
    memcpy(new_portable_info_string_lengths, portable->info_string_lengths, sizeof(int32_t) * portable->info_string_lengths_length);
    free(portable->info_string_lengths);
    portable->info_string_lengths = new_portable_info_string_lengths;
    portable->info_string_lengths_capacity = new_portable_info_string_lengths_capacity;
  }
  
  portable->info_string_lengths[portable->info_string_lengths_length] = info_string_length;

  portable->info_string_lengths_length++;
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
  new_portable_field[3] = SPVM_PORTABLE_push_symbol(portable, field->name);
  new_portable_field[4] = SPVM_PORTABLE_push_symbol(portable, field->abs_name);
  new_portable_field[5] = SPVM_PORTABLE_push_symbol(portable, field->signature);
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
  new_portable_package_var[1] = SPVM_PORTABLE_push_symbol(portable, package_var->name);
  new_portable_package_var[2] = SPVM_PORTABLE_push_symbol(portable, package_var->abs_name);
  new_portable_package_var[3] = SPVM_PORTABLE_push_symbol(portable, package_var->signature);
  if (package_var->type->basic_type) {
    new_portable_package_var[4] = package_var->type->basic_type->id;
  }
  else {
    new_portable_package_var[4] = -1;
  }
  new_portable_package_var[5] = package_var->type->dimension;
  new_portable_package_var[6] = package_var->type->flag;
  assert(package_var->package);
  new_portable_package_var[7] = package_var->package->id;
  
  portable->package_vars_length++;
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
  new_portable_package[1] = SPVM_PORTABLE_push_symbol(portable, package->name);
  if (package->sub_destructor) {
    new_portable_package[2] = package->sub_destructor->id;
  }
  else {
    new_portable_package[2] = -1;
  }
  new_portable_package[3] = package->category;
  new_portable_package[4] = SPVM_PORTABLE_push_symbol(portable, package->load_path);
  new_portable_package[5] = package->flag;
  
  portable->packages_length++;
}

void SPVM_PORTABLE_free(SPVM_PORTABLE* portable) {
  
  if (!portable->is_static) {
    free(portable->basic_types);
    portable->basic_types = NULL;

    free(portable->fields);
    portable->fields = NULL;

    free(portable->subs);
    portable->subs = NULL;

    free(portable->mys);
    portable->mys = NULL;

    free(portable->info_package_var_ids);
    portable->info_package_var_ids = NULL;

    free(portable->info_sub_ids);
    portable->info_sub_ids = NULL;

    free(portable->info_field_ids);
    portable->info_field_ids = NULL;

    free(portable->info_types);
    portable->info_types = NULL;

    free(portable->mys);
    portable->info_constants = NULL;

    free(portable->mys);
    portable->mys = NULL;
    
    free(portable->info_switch_info_ints);
    portable->info_switch_info_ints = NULL;
    
    free(portable->info_long_values);
    portable->info_long_values = NULL;
    
    free(portable->info_double_values);
    portable->info_double_values = NULL;
    
    free(portable->info_string_lengths);
    portable->info_string_lengths = NULL;
    
    free(portable->opcodes);
    portable->opcodes = NULL;
    
    for (int32_t i = 0; i < portable->symbols_length; i++) {
      free(portable->symbols[i]);
      portable->symbols[i] = NULL;
    }
    free(portable->symbols);
    portable->symbols = NULL;
    
    for (int32_t i = 0; i < portable->info_string_values_length; i++) {
      free(portable->info_string_values[i]);
      portable->info_string_values[i] = NULL;
    }
    free(portable->info_string_values);
    portable->info_string_values = NULL;
    
    free(portable);
  }
}
