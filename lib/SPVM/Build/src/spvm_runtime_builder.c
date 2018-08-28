#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_runtime_builder.h"

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
#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
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
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_package_var.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_arg.h"
#include "spvm_runtime_info_type.h"
#include "spvm_runtime_info_switch_info.h"
#include "spvm_runtime_info_case_info.h"
#include "spvm_my.h"
#include "spvm_portable.h"

SPVM_RUNTIME* SPVM_RUNTIME_BUILDER_build_runtime(SPVM_PORTABLE* portable) {

  SPVM_RUNTIME* runtime = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME));
  
  SPVM_ENV* env = (SPVM_ENV*)SPVM_RUNTIME_API_get_env_runtime();
  
  runtime->env = env;

  // Copy portable strings to runtime strings
  SPVM_LIST* strings = SPVM_LIST_new(portable->strings_length);
  for (int32_t i = 0; i < portable->strings_length; i++) {
    char* string = portable->strings[i];
    int32_t string_length = (int32_t)strlen(string);
    
    char* new_string = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(string_length + 1);
    memcpy(new_string, string, string_length);
    new_string[string_length] = '\0';
    
    SPVM_LIST_push(strings, new_string);
  }
  runtime->strings = strings;
  
  // Set global runtime
  SPVM_RUNTIME_API_set_runtime(env, runtime);
  
  runtime->info_switch_infos = SPVM_LIST_new(0);
  
  // Build runtime sub infos
  runtime->subs = SPVM_LIST_new(0);
  runtime->sub_symtable = SPVM_HASH_new(0);

  // Build runtime package infos
  runtime->packages = SPVM_LIST_new(0);
  runtime->package_symtable = SPVM_HASH_new(0);
  
  runtime->basic_types = (SPVM_RUNTIME_BASIC_TYPE*)portable->basic_types;
  runtime->basic_types_length = portable->basic_types_length;

  runtime->fields = (SPVM_RUNTIME_FIELD*)portable->fields;
  runtime->fields_length = portable->fields_length;

  runtime->package_vars = (SPVM_RUNTIME_PACKAGE_VAR*)portable->package_vars;
  runtime->package_vars_length = portable->package_vars_length;
  
  runtime->args = (SPVM_RUNTIME_ARG*)portable->args;
  runtime->info_types = (SPVM_RUNTIME_INFO_TYPE*)portable->info_types;
  runtime->info_field_ids = portable->info_field_ids;
  runtime->info_package_var_ids = portable->info_package_var_ids;
  runtime->info_sub_ids = portable->info_sub_ids;
  runtime->opcodes = portable->opcodes;
  
  // build runtime info_switch_info info_switch_infos
  int32_t info_switch_info_ints_index = 0;
  for (size_t i = 0; i < portable->info_switch_infos_length; i++) {
    int32_t* portable_info_switch_info_ints = (int32_t*)&portable->info_switch_info_ints[info_switch_info_ints_index];

    SPVM_RUNTIME_INFO_SWITCH_INFO* runtime_info_switch_info = SPVM_RUNTIME_INFO_SWITCH_INFO_new();
    runtime_info_switch_info->default_opcode_rel_index = portable_info_switch_info_ints[0];
    int32_t case_infos_length = portable_info_switch_info_ints[1];
    
    runtime_info_switch_info->case_infos = SPVM_LIST_new(0);
    for (int32_t case_info_index = 0; case_info_index < case_infos_length; case_info_index++) {
      SPVM_RUNTIME_INFO_CASE_INFO* info_case_info = SPVM_RUNTIME_INFO_CASE_INFO_new();
      
      info_case_info->match = portable_info_switch_info_ints[2 + (2 * case_info_index)];
      info_case_info->opcode_rel_index = portable_info_switch_info_ints[2 + (2 * case_info_index) + 1];
      
      SPVM_LIST_push(runtime_info_switch_info->case_infos, info_case_info);
    }
    
    info_switch_info_ints_index += 2 + case_infos_length * 2;
    
    SPVM_LIST_push(runtime->info_switch_infos, runtime_info_switch_info);
  }

  // build package variable symtable
  runtime->package_var_symtable = SPVM_HASH_new(0);
  for (int32_t package_var_id = 0; package_var_id < runtime->package_vars_length; package_var_id++) {
    SPVM_RUNTIME_PACKAGE_VAR* runtime_package_var = &runtime->package_vars[package_var_id];
    const char* runtime_package_var_name = SPVM_LIST_fetch(runtime->strings, runtime_package_var->name_id);
    SPVM_HASH_insert(runtime->package_var_symtable, runtime_package_var_name, strlen(runtime_package_var_name), runtime_package_var);
  }

  // build subs
  for (size_t i = 0; i < portable->subs_unit * portable->subs_length; i += portable->subs_unit) {
    int32_t* portable_sub = (int32_t*)&portable->subs[i];
    
    SPVM_RUNTIME_SUB* runtime_sub = SPVM_RUNTIME_SUB_new();
    runtime_sub->id = portable_sub[0];
    runtime_sub->flag = portable_sub[1];
    runtime_sub->name = SPVM_LIST_fetch(runtime->strings, portable_sub[2]);
    runtime_sub->abs_name = SPVM_LIST_fetch(runtime->strings, portable_sub[3]);
    runtime_sub->signature = SPVM_LIST_fetch(runtime->strings, portable_sub[4]);
    runtime_sub->package_id = portable_sub[5];
    runtime_sub->file = SPVM_LIST_fetch(runtime->strings, portable_sub[6]);
    runtime_sub->line = portable_sub[7];
    runtime_sub->args_alloc_length = portable_sub[8];
    runtime_sub->vars_alloc_length = portable_sub[9];
    runtime_sub->return_basic_type_id = portable_sub[10];
    runtime_sub->return_type_dimension = portable_sub[11];
    runtime_sub->return_type_flag = portable_sub[12];
    runtime_sub->opcode_base = portable_sub[13];
    runtime_sub->mortal_stack_length = portable_sub[14];
    runtime_sub->arg_ids_base = portable_sub[15];
    runtime_sub->arg_ids_length = portable_sub[16];
    runtime_sub->info_package_var_ids_base = portable_sub[17];
    runtime_sub->info_package_var_ids_length = portable_sub[18];
    runtime_sub->info_field_ids_base = portable_sub[19];
    runtime_sub->info_field_ids_length = portable_sub[20];
    runtime_sub->info_sub_ids_base = portable_sub[21];
    runtime_sub->info_sub_ids_length = portable_sub[22];
    runtime_sub->info_types_base = portable_sub[23];
    runtime_sub->info_types_length = portable_sub[24];
    runtime_sub->info_switch_infos_base = portable_sub[25];
    runtime_sub->info_switch_infos_length = portable_sub[26];
    runtime_sub->info_longs_base = portable_sub[21];
    runtime_sub->info_longs_length = portable_sub[22];

    SPVM_LIST_push(runtime->subs, runtime_sub);
  }

  // build packages
  for (size_t i = 0; i < portable->packages_unit * portable->packages_length; i += portable->packages_unit) {
    int32_t* portable_package = (int32_t*)&portable->packages[i];
    
    SPVM_RUNTIME_PACKAGE* runtime_package = SPVM_RUNTIME_PACKAGE_new();
    runtime_package->id = portable_package[0];
    runtime_package->name = SPVM_LIST_fetch(runtime->strings, portable_package[1]);
    runtime_package->destructor_sub_id = portable_package[2];
    runtime_package->category = portable_package[3];
    
    SPVM_LIST_push(runtime->packages, runtime_package);
  }

  // build package symtable
  for (int32_t package_id = 0; package_id < runtime->packages->length; package_id++) {
    
    SPVM_RUNTIME_PACKAGE* package = SPVM_LIST_fetch(runtime->packages, package_id);
    SPVM_HASH_insert(runtime->package_symtable, package->name, strlen(package->name), package);
    
    package->fields = SPVM_LIST_new(0);
    package->field_symtable = SPVM_HASH_new(0);
    package->field_signatures = SPVM_LIST_new(0);
    package->field_signature_symtable = SPVM_HASH_new(0);
    package->object_field_indexes = SPVM_LIST_new(0);
    package->package_vars = SPVM_LIST_new(0);
    package->package_var_symtable = SPVM_HASH_new(0);
    package->package_var_signatures = SPVM_LIST_new(0);
    package->package_var_signature_symtable = SPVM_HASH_new(0);
    package->subs = SPVM_LIST_new(0);
    package->sub_symtable = SPVM_HASH_new(0);
    package->sub_signatures = SPVM_LIST_new(0);
    package->sub_signature_symtable = SPVM_HASH_new(0);
    package->has_interface_cache_symtable = SPVM_HASH_new(0);
  }

  // Register field info to package
  for (int32_t field_id = 0; field_id < runtime->fields_length; field_id++) {
    SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
    
    int32_t package_id = field->package_id;
    
    SPVM_RUNTIME_PACKAGE* package = SPVM_LIST_fetch(runtime->packages, package_id);
    
    SPVM_LIST_push(package->fields, field);
    const char* field_name = SPVM_LIST_fetch(runtime->strings, field->name_id);
    SPVM_HASH_insert(package->field_symtable, field_name, strlen(field_name), field);
    
    const char* field_signature = SPVM_LIST_fetch(runtime->strings, field->signature_id);
    SPVM_LIST_push(package->field_signatures, field_signature);
    SPVM_HASH_insert(package->field_signature_symtable, field_signature, strlen(field_signature), field);
    
    if (SPVM_RUNTIME_API_is_object_type(env, field->basic_type_id, field->type_dimension, field->type_flag)) {
      SPVM_LIST_push(package->object_field_indexes, field->index);
    }
  }

  // Register package_var info to package
  for (int32_t package_var_id = 0; package_var_id < runtime->package_vars_length; package_var_id++) {
    SPVM_RUNTIME_PACKAGE_VAR* package_var = &runtime->package_vars[package_var_id];
    
    int32_t package_id = package_var->package_id;
    
    SPVM_RUNTIME_PACKAGE* package = SPVM_LIST_fetch(runtime->packages, package_id);
    
    SPVM_LIST_push(package->package_vars, package_var);
    const char* package_var_name = SPVM_LIST_fetch(runtime->strings, package_var->name_id);
    SPVM_HASH_insert(package->package_var_symtable, package_var_name, strlen(package_var_name), package_var);
    
    const char* package_var_signature = SPVM_LIST_fetch(runtime->strings, package_var->signature_id);
    SPVM_LIST_push(package->package_var_signatures, package_var_signature);
    SPVM_HASH_insert(package->package_var_signature_symtable, package_var_signature, strlen(package_var_signature), package_var);
  }

  // Register sub info to package
  for (int32_t sub_id = 0; sub_id < runtime->subs->length; sub_id++) {
    SPVM_RUNTIME_SUB* sub = SPVM_LIST_fetch(runtime->subs, sub_id);
    
    int32_t package_id = sub->package_id;
    
    SPVM_RUNTIME_PACKAGE* package = SPVM_LIST_fetch(runtime->packages, package_id);
    
    SPVM_LIST_push(package->subs, sub);
    SPVM_HASH_insert(package->sub_symtable, sub->name, strlen(sub->name), sub);
    
    SPVM_LIST_push(package->sub_signatures, sub->signature);
    SPVM_HASH_insert(package->sub_signature_symtable, sub->signature, strlen(sub->signature), sub);
  }

  // build runtime basic type symtable
  runtime->basic_type_symtable = SPVM_HASH_new(0);
  for (int32_t basic_type_id = 0; basic_type_id < runtime->basic_types_length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = &runtime->basic_types[basic_type_id];
    const char* runtime_basic_type_name = SPVM_LIST_fetch(runtime->strings, runtime_basic_type->name_id);
    SPVM_HASH_insert(runtime->basic_type_symtable, runtime_basic_type_name, strlen(runtime_basic_type_name), runtime_basic_type);
  }
  
  // build runtime field symtable
  runtime->field_symtable = SPVM_HASH_new(0);
  for (int32_t field_id = 0; field_id < runtime->fields_length; field_id++) {
    SPVM_RUNTIME_FIELD* runtime_field = &runtime->fields[field_id];
    const char* runtime_field_name = SPVM_LIST_fetch(runtime->strings, runtime_field->name_id);
    SPVM_HASH_insert(runtime->field_symtable, runtime_field_name, strlen(runtime_field_name), runtime_field);
  }

  // build sub symtable
  for (int32_t sub_id = 0; sub_id < runtime->subs->length; sub_id++) {
    SPVM_RUNTIME_SUB* runtime_sub = SPVM_LIST_fetch(runtime->subs, sub_id);
    SPVM_HASH_insert(runtime->sub_symtable, runtime_sub->abs_name, strlen(runtime_sub->abs_name), runtime_sub);
  }

  // Initialize Package Variables
  runtime->package_vars_heap = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_VALUE) * (runtime->package_vars_length + 1));

  runtime->mortal_stack_capacity = 1;

  runtime->mortal_stack = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_OBJECT*) * runtime->mortal_stack_capacity);
  
  return runtime;
}
