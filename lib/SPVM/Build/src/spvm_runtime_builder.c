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
  
  runtime->mortal_stack_capacity = 1;

  runtime->mortal_stack = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_OBJECT*) * runtime->mortal_stack_capacity);
  
  // Build runtime basic type infos
  runtime->basic_types = SPVM_LIST_new(0);
  runtime->basic_type_symtable = SPVM_HASH_new(0);

  // Build runtime field infos
  runtime->fields = SPVM_LIST_new(0);
  runtime->field_symtable = SPVM_HASH_new(0);

  // Build runtime package_var infos
  runtime->package_vars = SPVM_LIST_new(0);
  runtime->package_var_symtable = SPVM_HASH_new(0);
  
  runtime->args = SPVM_LIST_new(0);
  runtime->info_package_var_ids = SPVM_LIST_new(0);
  runtime->info_field_ids = SPVM_LIST_new(0);
  runtime->info_sub_ids = SPVM_LIST_new(0);
  runtime->info_types = SPVM_LIST_new(0);
  
  // Build runtime sub infos
  runtime->subs = SPVM_LIST_new(0);
  runtime->sub_symtable = SPVM_HASH_new(0);

  // Build runtime package infos
  runtime->packages = SPVM_LIST_new(0);
  runtime->package_symtable = SPVM_HASH_new(0);
  
  // build runtime basic types
  for (size_t i = 0; i < portable->basic_types_unit * portable->basic_types_length; i += portable->basic_types_unit) {
    int32_t* portable_basic_type = (int32_t*)&portable->basic_types[i];
    
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = SPVM_RUNTIME_BASIC_TYPE_new();
    runtime_basic_type->name = SPVM_LIST_fetch(runtime->strings, portable_basic_type[0]);
    runtime_basic_type->id = portable_basic_type[1];
    runtime_basic_type->category = portable_basic_type[2];
    runtime_basic_type->package_id = portable_basic_type[3];
    
    SPVM_LIST_push(runtime->basic_types, runtime_basic_type);
  }

  // build runtime basic type symtable
  for (int32_t basic_type_id = 0; basic_type_id < runtime->basic_types->length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = SPVM_LIST_fetch(runtime->basic_types, basic_type_id);
    SPVM_HASH_insert(runtime->basic_type_symtable, runtime_basic_type->name, strlen(runtime_basic_type->name), runtime_basic_type);
  }

  // build runtime arg args
  for (size_t i = 0; i < portable->args_unit * portable->args_length; i += portable->args_unit) {
    int32_t* portable_arg = (int32_t*)&portable->args[i];
    
    SPVM_RUNTIME_ARG* runtime_arg = SPVM_RUNTIME_ARG_new();
    runtime_arg->var_id = portable_arg[0];
    runtime_arg->basic_type_id = portable_arg[1];
    runtime_arg->type_dimension = portable_arg[2];
    runtime_arg->type_flag = portable_arg[3];
    
    SPVM_LIST_push(runtime->args, runtime_arg);
  }

  // build runtime info_type info_types
  for (size_t i = 0; i < portable->info_types_unit * portable->info_types_length; i += portable->info_types_unit) {
    int32_t* portable_info_type = (int32_t*)&portable->info_types[i];
    
    SPVM_RUNTIME_INFO_TYPE* runtime_info_type = SPVM_RUNTIME_INFO_TYPE_new();
    runtime_info_type->basic_type_id = portable_info_type[0];
    runtime_info_type->dimension = portable_info_type[1];
    runtime_info_type->flag = portable_info_type[2];
    
    SPVM_LIST_push(runtime->info_types, runtime_info_type);
  }
  
  // build runtime package_var_id package_var_ids
  for (size_t i = 0; i < portable->info_package_var_ids_unit * portable->info_package_var_ids_length; i += portable->info_package_var_ids_unit) {
    int32_t info_package_var_id = portable->info_package_var_ids[i];
    
    SPVM_LIST_push(runtime->info_package_var_ids, info_package_var_id);
  }

  // build runtime field_id field_ids
  for (size_t i = 0; i < portable->info_field_ids_unit * portable->info_field_ids_length; i += portable->info_field_ids_unit) {
    int32_t info_field_id = portable->info_field_ids[i];
    
    SPVM_LIST_push(runtime->info_field_ids, info_field_id);
  }

  // build runtime sub_id sub_ids
  for (size_t i = 0; i < portable->info_sub_ids_unit * portable->info_sub_ids_length; i += portable->info_sub_ids_unit) {
    int32_t info_sub_id = portable->info_sub_ids[i];
    
    SPVM_LIST_push(runtime->info_sub_ids, info_sub_id);
  }
  
  // build_runtime fields
  for (size_t i = 0; i < portable->fields_unit * portable->fields_length; i += portable->fields_unit) {
    int32_t* portable_field = (int32_t*)&portable->fields[i];
    
    SPVM_RUNTIME_FIELD* runtime_field = SPVM_RUNTIME_FIELD_new();
    runtime_field->id = portable_field[0];
    runtime_field->index = portable_field[1];
    runtime_field->flag = portable_field[2];
    runtime_field->name = SPVM_LIST_fetch(runtime->strings, portable_field[3]);
    runtime_field->abs_name = SPVM_LIST_fetch(runtime->strings, portable_field[4]);
    runtime_field->signature = SPVM_LIST_fetch(runtime->strings, portable_field[5]);
    runtime_field->basic_type_id = portable_field[6];
    runtime_field->type_dimension = portable_field[7];
    runtime_field->type_flag = portable_field[8];
    runtime_field->package_id = portable_field[9];
    
    SPVM_LIST_push(runtime->fields, runtime_field);
  }
  
  // build runtime field symtable
  for (int32_t field_id = 0; field_id < runtime->fields->length; field_id++) {
    SPVM_RUNTIME_FIELD* runtime_field = SPVM_LIST_fetch(runtime->fields, field_id);
    SPVM_HASH_insert(runtime->field_symtable, runtime_field->name, strlen(runtime_field->name), runtime_field);
  }

  // build package variables
  for (size_t i = 0; i < portable->package_vars_unit * portable->package_vars_length; i += portable->package_vars_unit) {
    int32_t* portable_package_var = (int32_t*)&portable->package_vars[i];
    
    SPVM_RUNTIME_PACKAGE_VAR* runtime_package_var = SPVM_RUNTIME_PACKAGE_VAR_new();
    runtime_package_var->id = portable_package_var[0];
    runtime_package_var->name = SPVM_LIST_fetch(runtime->strings, portable_package_var[1]);
    runtime_package_var->abs_name = SPVM_LIST_fetch(runtime->strings, portable_package_var[2]);
    runtime_package_var->signature = SPVM_LIST_fetch(runtime->strings, portable_package_var[3]);
    runtime_package_var->basic_type_id = portable_package_var[4];
    runtime_package_var->type_dimension = portable_package_var[5];
    runtime_package_var->type_flag = portable_package_var[6];
    runtime_package_var->package_id = portable_package_var[7];
    
    SPVM_LIST_push(runtime->package_vars, runtime_package_var);
  }

  // build package variable symtable
  for (int32_t package_var_id = 0; package_var_id < runtime->package_vars->length; package_var_id++) {
    SPVM_RUNTIME_PACKAGE_VAR* runtime_package_var = SPVM_LIST_fetch(runtime->package_vars, package_var_id);
    SPVM_HASH_insert(runtime->package_var_symtable, runtime_package_var->name, strlen(runtime_package_var->name), runtime_package_var);
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

    SPVM_LIST_push(runtime->subs, runtime_sub);
  }

  // build sub symtable
  for (int32_t sub_id = 0; sub_id < runtime->subs->length; sub_id++) {
    SPVM_RUNTIME_SUB* runtime_sub = SPVM_LIST_fetch(runtime->subs, sub_id);
    SPVM_HASH_insert(runtime->sub_symtable, runtime_sub->abs_name, strlen(runtime_sub->abs_name), runtime_sub);
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
  for (int32_t field_id = 0; field_id < runtime->fields->length; field_id++) {
    SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(runtime->fields, field_id);
    
    int32_t package_id = field->package_id;
    
    SPVM_RUNTIME_PACKAGE* package = SPVM_LIST_fetch(runtime->packages, package_id);
    
    SPVM_LIST_push(package->fields, field);
    SPVM_HASH_insert(package->field_symtable, field->name, strlen(field->name), field);
    
    SPVM_LIST_push(package->field_signatures, field->signature);
    SPVM_HASH_insert(package->field_signature_symtable, field->signature, strlen(field->signature), field);
    
    if (SPVM_RUNTIME_API_is_object_type(env, field->basic_type_id, field->type_dimension, field->type_flag)) {
      SPVM_LIST_push(package->object_field_indexes, field->index);
    }
  }

  // Register package_var info to package
  for (int32_t package_var_id = 0; package_var_id < runtime->package_vars->length; package_var_id++) {
    SPVM_RUNTIME_PACKAGE_VAR* package_var = SPVM_LIST_fetch(runtime->package_vars, package_var_id);
    
    int32_t package_id = package_var->package_id;
    
    SPVM_RUNTIME_PACKAGE* package = SPVM_LIST_fetch(runtime->packages, package_id);
    
    SPVM_LIST_push(package->package_vars, package_var);
    SPVM_HASH_insert(package->package_var_symtable, package_var->name, strlen(package_var->name), package_var);
    
    SPVM_LIST_push(package->package_var_signatures, package_var->signature);
    SPVM_HASH_insert(package->package_var_signature_symtable, package_var->signature, strlen(package_var->signature), package_var);
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

  // Initialize Package Variables
  runtime->package_vars_heap = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_VALUE) * (runtime->package_vars->length + 1));

  return runtime;
}
