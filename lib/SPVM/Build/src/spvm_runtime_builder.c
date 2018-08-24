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
#include "spvm_my.h"

int32_t SPVM_RUNTIME_BUILDER_push_runtime_string(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, const char* string) {
  
  
  int32_t id = runtime->strings_length;
  if (runtime->strings_length >= runtime->strings_capacity) {
    int32_t new_strings_capacity = runtime->strings_capacity * 2;
    char** new_strings = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * new_strings_capacity);
    memcpy(new_strings, runtime->strings, sizeof(char*) * runtime->strings_length);
    free(runtime->strings);
    runtime->strings = new_strings;
    runtime->strings_capacity = new_strings_capacity;
  }
  
  runtime->strings[runtime->strings_length] = string;
  runtime->strings_length++;
  
  return id;
}

void SPVM_RUNTIME_BUILDER_push_portable_arg(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_MY* my) {
  
  if (runtime->portable_args_length >= runtime->portable_args_capacity) {
    int32_t new_portable_args_capacity = runtime->portable_args_capacity * 2;
    int32_t* new_portable_args = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_args_unit * new_portable_args_capacity);
    memcpy(new_portable_args, runtime->portable_args, sizeof(int32_t) * runtime->portable_args_unit * runtime->portable_args_length);
    free(runtime->portable_args);
    runtime->portable_args = new_portable_args;
    runtime->portable_args_capacity = new_portable_args_capacity;
  }
  
  int32_t* new_portable_arg = (int32_t*)&runtime->portable_args[runtime->portable_args_unit * runtime->portable_args_length];
  new_portable_arg[0] = my->var_id;
  new_portable_arg[1] = my->type->basic_type->id;
  new_portable_arg[2] = my->type->dimension;
  new_portable_arg[3] = my->type->flag;

  runtime->portable_args_length++;
}

void SPVM_RUNTIME_BUILDER_push_portable_basic_type(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_BASIC_TYPE* basic_type) {
  
  if (runtime->portable_basic_types_length >= runtime->portable_basic_types_capacity) {
    int32_t new_portable_basic_types_capacity = runtime->portable_basic_types_capacity * 2;
    int32_t* new_portable_basic_types = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_basic_types_unit * new_portable_basic_types_capacity);
    memcpy(new_portable_basic_types, runtime->portable_basic_types, sizeof(int32_t) * runtime->portable_basic_types_unit * runtime->portable_basic_types_length);
    free(runtime->portable_basic_types);
    runtime->portable_basic_types = new_portable_basic_types;
    runtime->portable_basic_types_capacity = new_portable_basic_types_capacity;
  }
  
  int32_t* new_portable_basic_type = (int32_t*)&runtime->portable_basic_types[runtime->portable_basic_types_unit * runtime->portable_basic_types_length];
  new_portable_basic_type[0] = SPVM_RUNTIME_BUILDER_push_runtime_string(compiler, runtime, basic_type->name);
  new_portable_basic_type[1] = basic_type->id;
  new_portable_basic_type[2] = basic_type->category;
  if (basic_type->package) {
    new_portable_basic_type[3] = basic_type->package->id;
  }
  else {
    new_portable_basic_type[3] = -1;
  }
  runtime->portable_basic_types_length++;
}

void SPVM_RUNTIME_BUILDER_push_portable_field(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_FIELD* field) {
  
  if (runtime->portable_fields_length >= runtime->portable_fields_capacity) {
    int32_t new_portable_fields_capacity = runtime->portable_fields_capacity * 2;
    int32_t* new_portable_fields = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_fields_unit * new_portable_fields_capacity);
    memcpy(new_portable_fields, runtime->portable_fields, sizeof(int32_t) * runtime->portable_fields_unit * runtime->portable_fields_length);
    free(runtime->portable_fields);
    runtime->portable_fields = new_portable_fields;
    runtime->portable_fields_capacity = new_portable_fields_capacity;
  }
  
  int32_t* new_portable_field = (int32_t*)&runtime->portable_fields[runtime->portable_fields_unit * runtime->portable_fields_length];

  new_portable_field[0] = field->id;
  new_portable_field[1] = field->index;
  new_portable_field[2] = field->flag;
  new_portable_field[3] = SPVM_RUNTIME_BUILDER_push_runtime_string(compiler, runtime, field->name);
  new_portable_field[4] = SPVM_RUNTIME_BUILDER_push_runtime_string(compiler, runtime, field->abs_name);
  new_portable_field[5] = SPVM_RUNTIME_BUILDER_push_runtime_string(compiler, runtime, field->signature);
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
  
  runtime->portable_fields_length++;
}

void SPVM_RUNTIME_BUILDER_push_portable_package_var(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_PACKAGE_VAR* package_var) {
  
  if (runtime->portable_package_vars_length >= runtime->portable_package_vars_capacity) {
    int32_t new_portable_package_vars_capacity = runtime->portable_package_vars_capacity * 2;
    int32_t* new_portable_package_vars = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_package_vars_unit * new_portable_package_vars_capacity);
    memcpy(new_portable_package_vars, runtime->portable_package_vars, sizeof(int32_t) * runtime->portable_package_vars_unit * runtime->portable_package_vars_length);
    free(runtime->portable_package_vars);
    runtime->portable_package_vars = new_portable_package_vars;
    runtime->portable_package_vars_capacity = new_portable_package_vars_capacity;
  }
  
  int32_t* new_portable_package_var = (int32_t*)&runtime->portable_package_vars[runtime->portable_package_vars_unit * runtime->portable_package_vars_length];

  new_portable_package_var[0] = package_var->id;
  new_portable_package_var[1] = SPVM_RUNTIME_BUILDER_push_runtime_string(compiler, runtime, package_var->name);
  new_portable_package_var[2] = SPVM_RUNTIME_BUILDER_push_runtime_string(compiler, runtime, package_var->abs_name);
  new_portable_package_var[3] = SPVM_RUNTIME_BUILDER_push_runtime_string(compiler, runtime, package_var->signature);
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
  
  runtime->portable_package_vars_length++;
}

void SPVM_RUNTIME_BUILDER_push_portable_sub(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_SUB* sub) {
  
  if (runtime->portable_subs_length >= runtime->portable_subs_capacity) {
    int32_t new_portable_subs_capacity = runtime->portable_subs_capacity * 2;
    int32_t* new_portable_subs = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_subs_unit * new_portable_subs_capacity);
    memcpy(new_portable_subs, runtime->portable_subs, sizeof(int32_t) * runtime->portable_subs_unit * runtime->portable_subs_length);
    free(runtime->portable_subs);
    runtime->portable_subs = new_portable_subs;
    runtime->portable_subs_capacity = new_portable_subs_capacity;
  }
  
  int32_t* new_portable_sub = (int32_t*)&runtime->portable_subs[runtime->portable_subs_unit * runtime->portable_subs_length];

  new_portable_sub[0] = sub->id;
  new_portable_sub[1] = sub->flag;
  new_portable_sub[2] = SPVM_RUNTIME_BUILDER_push_runtime_string(compiler, runtime, sub->name);
  new_portable_sub[3] = SPVM_RUNTIME_BUILDER_push_runtime_string(compiler, runtime, sub->abs_name);
  new_portable_sub[4] = SPVM_RUNTIME_BUILDER_push_runtime_string(compiler, runtime, sub->signature);
  if (sub->package) {
    new_portable_sub[5] = sub->package->id;
  }
  else {
    new_portable_sub[5] = -1;
  }

  new_portable_sub[6] = SPVM_RUNTIME_BUILDER_push_runtime_string(compiler, runtime, sub->file);
  new_portable_sub[7] = sub->line;
  new_portable_sub[8] = sub->args_alloc_length;
  new_portable_sub[9] = sub->vars_alloc_length;

  new_portable_sub[10] = sub->return_type->basic_type->id;
  new_portable_sub[11] = sub->return_type->dimension;
  new_portable_sub[12] = sub->return_type->flag;
  new_portable_sub[13] = sub->opcode_base;
  new_portable_sub[14] = sub->mortal_stack_length;
  new_portable_sub[15] = runtime->portable_args_length;
  new_portable_sub[16] = sub->args->length;
  
  SPVM_MY* my = sub->args;
  for (int32_t arg_id = 0; arg_id < sub->args->length; arg_id++) {
    SPVM_MY* my = SPVM_LIST_fetch(sub->args, arg_id);
    SPVM_RUNTIME_BUILDER_push_portable_arg(compiler, runtime, my);
  }

  runtime->portable_subs_length++;
}

void SPVM_RUNTIME_BUILDER_push_portable_package(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_PACKAGE* package) {
  
  if (runtime->portable_packages_length >= runtime->portable_packages_capacity) {
    int32_t new_portable_packages_capacity = runtime->portable_packages_capacity * 2;
    int32_t* new_portable_packages = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_packages_unit * new_portable_packages_capacity);
    memcpy(new_portable_packages, runtime->portable_packages, sizeof(int32_t) * runtime->portable_packages_unit * runtime->portable_packages_length);
    free(runtime->portable_packages);
    runtime->portable_packages = new_portable_packages;
    runtime->portable_packages_capacity = new_portable_packages_capacity;
  }
  
  int32_t* new_portable_package = (int32_t*)&runtime->portable_packages[runtime->portable_packages_unit * runtime->portable_packages_length];

  new_portable_package[0] = package->id;
  new_portable_package[1] = SPVM_RUNTIME_BUILDER_push_runtime_string(compiler, runtime, package->name);
  if (package->sub_destructor) {
    new_portable_package[2] = package->sub_destructor->id;
  }
  else {
    new_portable_package[2] = -1;
  }
  new_portable_package[3] = package->category;
  
  runtime->portable_packages_length++;
}

void SPVM_RUNTIME_BUILDER_build_runtime_info(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime) {
  
  // build runtime basic types
  for (size_t i = 0; i < runtime->portable_basic_types_unit * runtime->portable_basic_types_length; i += runtime->portable_basic_types_unit) {
    int32_t* portable_basic_type = (int32_t*)&runtime->portable_basic_types[i];
    
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = SPVM_RUNTIME_BASIC_TYPE_new();
    runtime_basic_type->name = runtime->strings[portable_basic_type[0]];
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

  // build runtime arg types
  for (size_t i = 0; i < runtime->portable_args_unit * runtime->portable_args_length; i += runtime->portable_args_unit) {
    int32_t* portable_arg = (int32_t*)&runtime->portable_args[i];
    
    SPVM_RUNTIME_ARG* runtime_arg = SPVM_RUNTIME_ARG_new();
    runtime_arg->var_id = portable_arg[0];
    runtime_arg->basic_type_id = portable_arg[1];
    runtime_arg->type_dimension = portable_arg[2];
    runtime_arg->type_flag = portable_arg[3];
    
    SPVM_LIST_push(runtime->args, runtime_arg);
  }
  
  // build_runtime fields
  for (size_t i = 0; i < runtime->portable_fields_unit * runtime->portable_fields_length; i += runtime->portable_fields_unit) {
    int32_t* portable_field = (int32_t*)&runtime->portable_fields[i];
    
    SPVM_RUNTIME_FIELD* runtime_field = SPVM_RUNTIME_FIELD_new(compiler);
    runtime_field->id = portable_field[0];
    runtime_field->index = portable_field[1];
    runtime_field->flag = portable_field[2];
    runtime_field->name = runtime->strings[portable_field[3]];
    runtime_field->abs_name = runtime->strings[portable_field[4]];
    runtime_field->signature = runtime->strings[portable_field[5]];
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
  for (size_t i = 0; i < runtime->portable_package_vars_unit * runtime->portable_package_vars_length; i += runtime->portable_package_vars_unit) {
    int32_t* portable_package_var = (int32_t*)&runtime->portable_package_vars[i];
    
    SPVM_RUNTIME_PACKAGE_VAR* runtime_package_var = SPVM_RUNTIME_PACKAGE_VAR_new(compiler);
    runtime_package_var->id = portable_package_var[0];
    runtime_package_var->name = runtime->strings[portable_package_var[1]];
    runtime_package_var->abs_name = runtime->strings[portable_package_var[2]];
    runtime_package_var->signature = runtime->strings[portable_package_var[3]];
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
  for (size_t i = 0; i < runtime->portable_subs_unit * runtime->portable_subs_length; i += runtime->portable_subs_unit) {
    int32_t* portable_sub = (int32_t*)&runtime->portable_subs[i];
    
    SPVM_RUNTIME_SUB* runtime_sub = SPVM_RUNTIME_SUB_new(compiler);
    runtime_sub->id = portable_sub[0];
    runtime_sub->flag = portable_sub[1];
    runtime_sub->name = runtime->strings[portable_sub[2]];
    runtime_sub->abs_name = runtime->strings[portable_sub[3]];
    runtime_sub->signature = runtime->strings[portable_sub[4]];
    runtime_sub->package_id = portable_sub[5];
    runtime_sub->file = runtime->strings[portable_sub[6]];
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

    SPVM_LIST_push(runtime->subs, runtime_sub);
  }

  // build sub symtable
  for (int32_t sub_id = 0; sub_id < runtime->subs->length; sub_id++) {
    SPVM_RUNTIME_SUB* runtime_sub = SPVM_LIST_fetch(runtime->subs, sub_id);
    SPVM_HASH_insert(runtime->sub_symtable, runtime_sub->abs_name, strlen(runtime_sub->abs_name), runtime_sub);
  }

  // build packages
  for (size_t i = 0; i < runtime->portable_packages_unit * runtime->portable_packages_length; i += runtime->portable_packages_unit) {
    int32_t* portable_package = (int32_t*)&runtime->portable_packages[i];
    
    SPVM_RUNTIME_PACKAGE* runtime_package = SPVM_RUNTIME_PACKAGE_new(compiler);
    runtime_package->id = portable_package[0];
    runtime_package->name = runtime->strings[portable_package[1]];
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
    
    if (SPVM_TYPE_is_object_type(compiler, field->basic_type_id, field->type_dimension, field->type_flag)) {
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


}

void SPVM_RUNTIME_BUILDER_bind_subs(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime) {
  for (int32_t sub_index = 0; sub_index < compiler->subs->length; sub_index++) {
    SPVM_RUNTIME_SUB* runtime_sub = SPVM_LIST_fetch(runtime->subs, sub_index);
    SPVM_SUB* sub = SPVM_LIST_fetch(compiler->subs, sub_index);
    
    runtime_sub->precompile_address = sub->precompile_address;
    runtime_sub->native_address = sub->native_address;
  }
}

SPVM_RUNTIME* SPVM_RUNTIME_BUILDER_build_runtime(SPVM_COMPILER* compiler) {
  
  SPVM_RUNTIME* runtime = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME));
  
  SPVM_ENV* env = (SPVM_ENV*)SPVM_RUNTIME_API_get_env_runtime();
  
  runtime->env = env;

  runtime->compiler = compiler;
  
  // Set global runtime
  SPVM_RUNTIME_API_set_runtime(env, runtime);
  
  // Initialize Package Variables
  runtime->package_vars_heap = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_VALUE) * (compiler->package_vars->length + 1));

  runtime->mortal_stack_capacity = 1;

  runtime->mortal_stack = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_OBJECT*) * runtime->mortal_stack_capacity);
  
  runtime->strings_capacity = 32;
  
  runtime->strings = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * runtime->strings_capacity);
  
  // Portable basic type
  runtime->portable_basic_types_capacity = 8;
  runtime->portable_basic_types_unit = 4;
  runtime->portable_basic_types = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_basic_types_unit * runtime->portable_basic_types_capacity);
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    SPVM_RUNTIME_BUILDER_push_portable_basic_type(compiler, runtime, basic_type);
  }
  
  // Build runtime basic type infos
  runtime->basic_types = SPVM_LIST_new(0);
  runtime->basic_type_symtable = SPVM_HASH_new(0);

  // Portable fields
  runtime->portable_fields_capacity = 8;
  runtime->portable_fields_unit = 10;
  runtime->portable_fields = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_fields_unit * runtime->portable_fields_capacity);
  for (int32_t field_id = 0; field_id < compiler->fields->length; field_id++) {
    SPVM_BASIC_TYPE* field = SPVM_LIST_fetch(compiler->fields, field_id);
    SPVM_RUNTIME_BUILDER_push_portable_field(compiler, runtime, field);
  }
  
  // Build runtime field infos
  runtime->fields = SPVM_LIST_new(0);
  runtime->field_symtable = SPVM_HASH_new(0);

  // Portable package_vars
  runtime->portable_package_vars_capacity = 8;
  runtime->portable_package_vars_unit = 8;
  runtime->portable_package_vars = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_package_vars_unit * runtime->portable_package_vars_capacity);
  for (int32_t package_var_id = 0; package_var_id < compiler->package_vars->length; package_var_id++) {
    SPVM_BASIC_TYPE* package_var = SPVM_LIST_fetch(compiler->package_vars, package_var_id);
    SPVM_RUNTIME_BUILDER_push_portable_package_var(compiler, runtime, package_var);
  }
  
  // Build runtime package_var infos
  runtime->package_vars = SPVM_LIST_new(0);
  runtime->package_var_symtable = SPVM_HASH_new(0);
  
  
  // Portable args
  runtime->portable_args_capacity = 8;
  runtime->portable_args_unit = 4;
  runtime->portable_args = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_args_unit * runtime->portable_args_capacity);

  runtime->args = SPVM_LIST_new(0);

  // Portable subs
  runtime->portable_subs_capacity = 8;
  runtime->portable_subs_unit = 17;
  runtime->portable_subs = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_subs_unit * runtime->portable_subs_capacity);
  for (int32_t sub_id = 0; sub_id < compiler->subs->length; sub_id++) {
    SPVM_BASIC_TYPE* sub = SPVM_LIST_fetch(compiler->subs, sub_id);
    SPVM_RUNTIME_BUILDER_push_portable_sub(compiler, runtime, sub);
  }
  
  // Build runtime sub infos
  runtime->subs = SPVM_LIST_new(0);
  runtime->sub_symtable = SPVM_HASH_new(0);

  // Portable packages
  runtime->portable_packages_capacity = 8;
  runtime->portable_packages_unit = 4;
  runtime->portable_packages = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_packages_unit * runtime->portable_packages_capacity);
  for (int32_t package_id = 0; package_id < compiler->packages->length; package_id++) {
    SPVM_BASIC_TYPE* package = SPVM_LIST_fetch(compiler->packages, package_id);
    SPVM_RUNTIME_BUILDER_push_portable_package(compiler, runtime, package);
  }
  
  // Build runtime package infos
  runtime->packages = SPVM_LIST_new(0);
  runtime->package_symtable = SPVM_HASH_new(0);

  SPVM_RUNTIME_BUILDER_build_runtime_info(compiler, runtime);
  
  compiler->runtime = runtime;

  return runtime;
}

