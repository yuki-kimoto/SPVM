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
#include "spvm_constant.h"
#include "spvm_my.h"

#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_package_var.h"
#include "spvm_runtime_arg.h"
#include "spvm_string_buffer.h"
#include "spvm_constant_pool.h"

SPVM_PORTABLE* SPVM_PORTABLE_new() {
  
  SPVM_PORTABLE* portable = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_PORTABLE));

  return portable;
}

SPVM_PORTABLE* SPVM_PORTABLE_build_portable(SPVM_COMPILER* compiler) {
  SPVM_PORTABLE* portable = SPVM_PORTABLE_new();

  portable->string_pool = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(compiler->string_pool->length + 1);
  portable->string_pool_length = compiler->string_pool->length;
  memcpy(portable->string_pool, compiler->string_pool->buffer, compiler->string_pool->length);
  
  // Global constant pool
  int32_t constant_pool_length = 0;
  for (int32_t package_index = 0; package_index < compiler->packages->length; package_index++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
    constant_pool_length += package->constant_pool->length;
  }
  portable->constant_pool = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * (constant_pool_length + 1));
  portable->constant_pool_length = constant_pool_length;
  int32_t constant_pool_index = 0;
  for (int32_t package_index = 0; package_index < compiler->packages->length; package_index++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
    package->constant_pool_base = constant_pool_index;
    memcpy(&portable->constant_pool[constant_pool_index], package->constant_pool->values, sizeof(int32_t) * package->constant_pool->length);
    constant_pool_index += package->constant_pool->length;
  }

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

  // Culcrate length
  int32_t args_total_length = 0;
  for (int32_t sub_index = 0; sub_index < compiler->subs->length; sub_index++) {
    SPVM_SUB* sub = SPVM_LIST_fetch(compiler->subs, sub_index);
    args_total_length += sub->args->length;
  }
  for (int32_t package_index = 0; package_index < compiler->packages->length; package_index++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
  }
  
  // Portable args
  portable->args = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_ARG) * (args_total_length + 1));

  // OPCode
  int32_t opcode_length = compiler->opcode_array->length;
  portable->opcodes_length = opcode_length;
  portable->opcodes = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int64_t) * (opcode_length + 1));
  memcpy(portable->opcodes, compiler->opcode_array->values, sizeof(int64_t) * opcode_length);

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

  new_portable_package->constant_pool_base = package->constant_pool_base;
  new_portable_package->no_dup_field_access_field_ids_constant_pool_id = package->no_dup_field_access_field_ids_constant_pool_id;
  new_portable_package->no_dup_package_var_access_package_var_ids_constant_pool_id = package->no_dup_package_var_access_package_var_ids_constant_pool_id;
  new_portable_package->no_dup_call_sub_sub_ids_constant_pool_id = package->no_dup_call_sub_sub_ids_constant_pool_id;
  new_portable_package->no_dup_basic_type_ids_constant_pool_id = package->no_dup_basic_type_ids_constant_pool_id;

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
    SPVM_MY* my_arg = SPVM_LIST_fetch(sub->args, arg_id);
    SPVM_PORTABLE_push_arg(compiler, portable, my_arg);
  }

  portable->subs_length++;
}

void SPVM_PORTABLE_push_arg(SPVM_COMPILER* compiler, SPVM_PORTABLE* portable, SPVM_MY* arg) {
  
  SPVM_RUNTIME_ARG* new_portable_arg = &portable->args[portable->args_length];
  new_portable_arg->basic_type_id = arg->type->basic_type->id;
  new_portable_arg->type_dimension = arg->type->dimension;
  new_portable_arg->type_flag = arg->type->flag;
  new_portable_arg->var_id = arg->var_id;
  new_portable_arg->runtime_type = arg->runtime_type;
  new_portable_arg->type_width = arg->type_width;

  portable->args_length++;
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

    free(portable->opcodes);
    portable->opcodes = NULL;
    
    free(portable);
  }
}
