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
#include "spvm_string_buffer.h"

SPVM_PORTABLE* SPVM_PORTABLE_new() {
  
  SPVM_PORTABLE* portable = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_PORTABLE));

  return portable;
}

SPVM_PORTABLE* SPVM_PORTABLE_build_portable(SPVM_COMPILER* compiler) {
  SPVM_PORTABLE* portable = SPVM_PORTABLE_new();

  portable->symbols_capacity = 32;

  portable->info_switch_info_ints_capacity = 8;

  portable->symbols = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * portable->symbols_capacity);
  
  portable->string_pool = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(compiler->string_pool->length + 1);
  portable->string_pool_length = compiler->string_pool->length;
  memcpy(portable->string_pool, compiler->string_pool->buffer, compiler->string_pool->length);

  // Portable basic type
  portable->basic_types = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_BASIC_TYPE) * (compiler->basic_types->length + 1));
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = &portable->basic_types[basic_type_id];
    runtime_basic_type->name_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, basic_type->name, strlen(basic_type->name) + 1);
    runtime_basic_type->id = basic_type->id;
    if (basic_type->package) {
      runtime_basic_type->package_id = basic_type->package->id;
    }
  }
  portable->basic_types_length = compiler->basic_types->length;
  
  // Portable fields(0 index is dummy)
  portable->fields = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_FIELD) * (compiler->fields->length + 1));
  portable->fields_length++;
  for (int32_t field_id = 0; field_id < compiler->fields->length; field_id++) {
    SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);
    SPVM_PORTABLE_push_field(compiler, portable, field);
  }
  
  // Portable package_vars(0 index is dummy)
  portable->package_vars = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_PACKAGE) * (compiler->package_vars->length + 1));
  portable->package_vars_length++;
  for (int32_t package_var_id = 0; package_var_id < compiler->package_vars->length; package_var_id++) {
    SPVM_PACKAGE_VAR* package_var = SPVM_LIST_fetch(compiler->package_vars, package_var_id);
    SPVM_PORTABLE_push_package_var(compiler, portable, package_var);
  }

  // Culcrate info length
  int32_t args_total_length = 0;
  int32_t info_types_total_length = 0;
  int32_t info_long_values_total_length = 0;
  int32_t info_double_values_total_length = 0;
  int32_t info_package_var_ids_total_length = 0;
  int32_t info_field_ids_total_length = 0;
  int32_t info_sub_ids_total_length = 0;
  int32_t info_string_values_total_length = 0;
  int32_t info_string_lengths_total_length = 0;
  for (int32_t sub_index = 0; sub_index < compiler->subs->length; sub_index++) {
    SPVM_SUB* sub = SPVM_LIST_fetch(compiler->subs, sub_index);
    args_total_length += sub->args->length;
  }
  for (int32_t package_index = 0; package_index < compiler->packages->length; package_index++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
    info_package_var_ids_total_length += package->info_package_var_ids->length;
    info_field_ids_total_length += package->info_field_ids->length;
    info_long_values_total_length += package->info_long_constants->length;
    info_double_values_total_length += package->info_double_constants->length;
    info_string_values_total_length += package->info_string_constants->length;
    info_string_lengths_total_length += package->info_string_constants->length;
    info_sub_ids_total_length += package->info_sub_ids->length;
    info_types_total_length += package->info_types->length;
  }
  
  // Portable args
  portable->args = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_MY) * (args_total_length + 1));

  // Portable info_types
  portable->info_types = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_INFO_TYPE) * (info_types_total_length + 1));

  // Portable long values
  portable->info_long_values = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int64_t) * (info_long_values_total_length + 1));

  // Portable double values
  portable->info_double_values = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(double) * (info_double_values_total_length + 1));

  // OPCode
  int32_t opcode_length = compiler->opcode_array->length;
  portable->opcodes_length = opcode_length;
  portable->opcodes = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int64_t) * (opcode_length + 1));
  memcpy(portable->opcodes, compiler->opcode_array->values, sizeof(int64_t) * opcode_length);

  // Portable info package var ids
  portable->info_package_var_ids = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * (info_package_var_ids_total_length + 1));

  // Portable info field  ids
  portable->info_field_ids = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * (info_field_ids_total_length + 1));

  // Portable info sub ids
  portable->info_sub_ids = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * (info_sub_ids_total_length + 1));

  // Portable string length
  portable->info_string_lengths = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * (info_string_lengths_total_length + 1));

  // Portable switch info
  portable->info_switch_info_ints = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * portable->info_switch_info_ints_capacity);

  // Portable string values
  portable->info_string_values = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * (info_string_values_total_length + 1));

  // Portable subs
  portable->subs = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_SUB) * (compiler->subs->length + 1));
  portable->subs_length++;
  for (int32_t sub_id = 0; sub_id < compiler->subs->length; sub_id++) {
    SPVM_SUB* sub = SPVM_LIST_fetch(compiler->subs, sub_id);
    SPVM_PORTABLE_push_sub(compiler, portable, sub);
  }
  
  // Portable packages(0 index is dummy)
  portable->packages = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_PACKAGE) * (compiler->packages->length + 1));
  portable->packages_length++;
  for (int32_t package_id = 0; package_id < compiler->packages->length; package_id++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_id);
    SPVM_PORTABLE_push_package(compiler, portable, package);
  }
  
  return portable;
}

void SPVM_PORTABLE_push_package(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, SPVM_PACKAGE* package) {
  
  SPVM_RUNTIME_PACKAGE* new_portable_package = &portable->packages[portable->packages_length];
  
  new_portable_package->id = package->id;
  new_portable_package->name_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, package->name, strlen(package->name) + 1);
  if (package->sub_destructor) {
    new_portable_package->destructor_sub_id = package->sub_destructor->id;
  }
  else {
    new_portable_package->destructor_sub_id = 0;
  }
  new_portable_package->category = package->category;
  new_portable_package->flag = package->flag;

  new_portable_package->info_package_var_ids_base = portable->info_package_var_ids_length;
  new_portable_package->info_package_var_ids_length = package->info_package_var_ids->length;

  new_portable_package->info_field_ids_base = portable->info_field_ids_length;
  new_portable_package->info_field_ids_length = package->info_field_ids->length;

  new_portable_package->info_long_values_base = portable->info_long_values_length;
  new_portable_package->info_long_values_length = package->info_long_constants->length;

  new_portable_package->info_double_values_base = portable->info_double_values_length;
  new_portable_package->info_double_values_length = package->info_double_constants->length;

  new_portable_package->info_string_values_base = portable->info_string_values_length;
  new_portable_package->info_string_values_length = package->info_string_constants->length;

  new_portable_package->info_sub_ids_base = portable->info_sub_ids_length;
  new_portable_package->info_sub_ids_length = package->info_sub_ids->length;

  new_portable_package->info_switch_infos_base = portable->info_switch_infos_length;
  new_portable_package->info_switch_infos_length = package->info_switch_infos->length;

  new_portable_package->info_types_base = portable->info_types_length;
  new_portable_package->info_types_length = package->info_types->length;

  for (int32_t info_package_var_ids_index = 0; info_package_var_ids_index < package->info_package_var_ids->length; info_package_var_ids_index++) {
    int32_t info_package_var_id = (intptr_t)SPVM_LIST_fetch(package->info_package_var_ids, info_package_var_ids_index);
    
    SPVM_PORTABLE_push_info_package_var_id(compiler, portable, info_package_var_id);
  }
  
  for (int32_t info_field_ids_index = 0; info_field_ids_index < package->info_field_ids->length; info_field_ids_index++) {
    int32_t info_field_id = (intptr_t)SPVM_LIST_fetch(package->info_field_ids, info_field_ids_index);
    
    SPVM_PORTABLE_push_info_field_id(compiler, portable, info_field_id);
  }

  for (int32_t info_long_values_index = 0; info_long_values_index < package->info_long_constants->length; info_long_values_index++) {
    SPVM_CONSTANT* constant = SPVM_LIST_fetch(package->info_long_constants, info_long_values_index);
    SPVM_PORTABLE_push_info_long_value(compiler, portable, constant->value.lval);
  }

  for (int32_t info_double_values_index = 0; info_double_values_index < package->info_double_constants->length; info_double_values_index++) {
    SPVM_CONSTANT* constant = SPVM_LIST_fetch(package->info_double_constants, info_double_values_index);
    SPVM_PORTABLE_push_info_double_value(compiler, portable, constant->value.dval);
  }

  for (int32_t info_string_values_index = 0; info_string_values_index < package->info_string_constants->length; info_string_values_index++) {
    SPVM_CONSTANT* constant = SPVM_LIST_fetch(package->info_string_constants, info_string_values_index);
    SPVM_PORTABLE_push_info_string_value(compiler, portable, (char*)constant->value.oval, constant->string_length);
  }

  for (int32_t info_string_lengths_index = 0; info_string_lengths_index < package->info_string_constants->length; info_string_lengths_index++) {
    SPVM_CONSTANT* constant = SPVM_LIST_fetch(package->info_string_constants, info_string_lengths_index);
    SPVM_PORTABLE_push_info_string_length(compiler, portable, constant->string_length);
  }

  for (int32_t info_sub_ids_index = 0; info_sub_ids_index < package->info_sub_ids->length; info_sub_ids_index++) {
    int32_t info_sub_id = (intptr_t)SPVM_LIST_fetch(package->info_sub_ids, info_sub_ids_index);
    
    SPVM_PORTABLE_push_info_sub_id(compiler, portable, info_sub_id);
  }

  for (int32_t info_switch_info_id = 0; info_switch_info_id < package->info_switch_infos->length; info_switch_info_id++) {
    SPVM_SWITCH_INFO* info_switch_info = SPVM_LIST_fetch(package->info_switch_infos, info_switch_info_id);
    SPVM_PORTABLE_push_info_switch_info(compiler, portable, info_switch_info);
  }

  for (int32_t info_type_id = 0; info_type_id < package->info_types->length; info_type_id++) {
    SPVM_TYPE* info_type = SPVM_LIST_fetch(package->info_types, info_type_id);
    SPVM_PORTABLE_push_info_type(compiler, portable, info_type);
  }

  portable->packages_length++;
}

void SPVM_PORTABLE_push_sub(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, SPVM_SUB* sub) {

  SPVM_RUNTIME_SUB* new_portable_sub = &portable->subs[portable->subs_length];

  new_portable_sub->id = sub->id;
  new_portable_sub->flag = sub->flag;
  new_portable_sub->name_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, sub->name, strlen(sub->name) + 1);
  new_portable_sub->signature_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, sub->signature, strlen(sub->signature) + 1);;
  if (sub->package) {
    new_portable_sub->package_id = sub->package->id;
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

  new_portable_sub->file_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, sub_file_base, strlen(sub_file_base) + 1);
  assert(new_portable_sub->file_id);
  new_portable_sub->line = sub->line;
  new_portable_sub->args_alloc_length = sub->args_alloc_length;
  new_portable_sub->return_basic_type_id = sub->return_type->basic_type->id;
  new_portable_sub->return_type_dimension = sub->return_type->dimension;
  new_portable_sub->return_type_flag = sub->return_type->flag;
  new_portable_sub->opcodes_base = sub->opcodes_base;
  new_portable_sub->mortal_stack_length = sub->mortal_stack_length;
  new_portable_sub->arg_ids_base = portable->args_length;
  new_portable_sub->arg_ids_length = sub->args->length;
  new_portable_sub->opcodes_length = sub->opcodes_length;
  new_portable_sub->call_type_id = sub->call_type_id;
  new_portable_sub->byte_vars_alloc_length = sub->byte_vars_alloc_length;
  new_portable_sub->short_vars_alloc_length = sub->short_vars_alloc_length;
  new_portable_sub->int_vars_alloc_length = sub->int_vars_alloc_length;
  new_portable_sub->long_vars_alloc_length = sub->long_vars_alloc_length;
  new_portable_sub->float_vars_alloc_length = sub->float_vars_alloc_length;
  new_portable_sub->double_vars_alloc_length = sub->double_vars_alloc_length;
  new_portable_sub->object_vars_alloc_length = sub->object_vars_alloc_length;
  new_portable_sub->ref_vars_alloc_length = sub->ref_vars_alloc_length;
  new_portable_sub->return_runtime_type = sub->return_runtime_type;
  
  for (int32_t arg_id = 0; arg_id < sub->args->length; arg_id++) {
    SPVM_MY* my = SPVM_LIST_fetch(sub->args, arg_id);
    SPVM_PORTABLE_push_arg(compiler, portable, my);
  }

  portable->subs_length++;
}

int32_t SPVM_PORTABLE_push_symbol(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, const char* string) {
  
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

void SPVM_PORTABLE_push_arg(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, SPVM_MY* arg) {
  
  SPVM_RUNTIME_MY* new_portable_arg = &portable->args[portable->args_length];
  new_portable_arg->basic_type_id = arg->type->basic_type->id;
  new_portable_arg->type_dimension = arg->type->dimension;
  new_portable_arg->type_flag = arg->type->flag;
  new_portable_arg->var_id = arg->var_id;
  new_portable_arg->runtime_type = arg->runtime_type;
  new_portable_arg->type_width = arg->type_width;

  portable->args_length++;
}

void SPVM_PORTABLE_push_info_type(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, SPVM_TYPE* info_type) {

  SPVM_RUNTIME_INFO_TYPE* new_portable_info_type = &portable->info_types[portable->info_types_length];
  new_portable_info_type->basic_type_id = info_type->basic_type->id;
  new_portable_info_type->dimension = info_type->dimension;
  new_portable_info_type->flag = info_type->flag;

  portable->info_types_length++;
}

void SPVM_PORTABLE_push_info_package_var_id(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, int32_t info_package_var_id) {

  int32_t* new_portable_info_package_var_id = (int32_t*)&portable->info_package_var_ids[portable->info_package_var_ids_length];
  new_portable_info_package_var_id[0] = info_package_var_id;

  portable->info_package_var_ids_length++;
}

void SPVM_PORTABLE_push_info_field_id(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, int32_t info_field_id) {

  int32_t* new_portable_info_field_id = (int32_t*)&portable->info_field_ids[portable->info_field_ids_length];
  *new_portable_info_field_id = info_field_id;

  portable->info_field_ids_length++;
}

void SPVM_PORTABLE_push_info_sub_id(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, int32_t info_sub_id) {

  int32_t* new_portable_info_sub_id = (int32_t*)&portable->info_sub_ids[portable->info_sub_ids_length];
  *new_portable_info_sub_id = info_sub_id;

  portable->info_sub_ids_length++;
}

void SPVM_PORTABLE_push_info_long_value(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, int64_t info_long_value) {

  portable->info_long_values[portable->info_long_values_length] = info_long_value;

  portable->info_long_values_length++;
}

void SPVM_PORTABLE_push_info_double_value(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, double info_double_value) {

  portable->info_double_values[portable->info_double_values_length] = info_double_value;

  portable->info_double_values_length++;
}

void SPVM_PORTABLE_push_info_string_value(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, const char* info_string_value, int32_t string_length) {

  portable->info_string_values[portable->info_string_values_length] = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(string_length + 1);
  memcpy(portable->info_string_values[portable->info_string_values_length], info_string_value, string_length);

  portable->info_string_values_length++;
}

void SPVM_PORTABLE_push_info_string_length(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, int32_t info_string_length) {

  portable->info_string_lengths[portable->info_string_lengths_length] = info_string_length;

  portable->info_string_lengths_length++;
}

void SPVM_PORTABLE_push_info_switch_info(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, SPVM_SWITCH_INFO* info_switch_info) {
  
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

void SPVM_PORTABLE_push_field(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, SPVM_FIELD* field) {
  
  SPVM_RUNTIME_FIELD* new_portable_field = &portable->fields[portable->fields_length];

  new_portable_field->id = field->id;
  new_portable_field->index = field->index;
  new_portable_field->flag = field->flag;
  new_portable_field->name_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, field->name, strlen(field->name) + 1);
  new_portable_field->signature_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, field->signature, strlen(field->signature) + 1);
  if (field->type->basic_type) {
    new_portable_field->basic_type_id = field->type->basic_type->id;
  }
  else {
    new_portable_field->basic_type_id = 0;
  }
  new_portable_field->type_dimension = field->type->dimension;
  if (field->package) {
    new_portable_field->package_id = field->package->id;
  }
  new_portable_field->runtime_type = field->runtime_type;
  
  portable->fields_length++;
}

void SPVM_PORTABLE_push_package_var(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, SPVM_PACKAGE_VAR* package_var) {
  
  SPVM_RUNTIME_PACKAGE_VAR* new_portable_package_var = &portable->package_vars[portable->package_vars_length];

  new_portable_package_var->id = package_var->id;
  new_portable_package_var->name_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, package_var->name, strlen(package_var->name) + 1);
  
  new_portable_package_var->signature_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, package_var->signature, strlen(package_var->signature) + 1);
  if (package_var->type->basic_type) {
    new_portable_package_var->basic_type_id = package_var->type->basic_type->id;
  }
  else {
    new_portable_package_var->basic_type_id = 0;
  }
  new_portable_package_var->type_dimension = package_var->type->dimension;
  new_portable_package_var->type_flag = package_var->type->flag;
  assert(package_var->package);
  new_portable_package_var->package_id = package_var->package->id;

  portable->package_vars_length++;
}

void SPVM_PORTABLE_free(SPVM_PORTABLE* portable) {
  
  if (!portable->is_static) {
    free(portable->basic_types);
    portable->basic_types = NULL;

    free(portable->fields);
    portable->fields = NULL;

    free(portable->subs);
    portable->subs = NULL;

    free(portable->info_package_var_ids);
    portable->info_package_var_ids = NULL;

    free(portable->info_sub_ids);
    portable->info_sub_ids = NULL;

    free(portable->info_field_ids);
    portable->info_field_ids = NULL;

    free(portable->info_types);
    portable->info_types = NULL;

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
