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

  // Opcode Length
  int32_t portable_opcode_length = compiler->opcode_array->length;
  portable->opcodes_length = portable_opcode_length;
  
  // Constant pool length
  int32_t portable_constant_pool_length = 0;
  for (int32_t package_index = 0; package_index < compiler->packages->length; package_index++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
    portable_constant_pool_length += package->constant_pool->length;
  }
  portable->constant_pool_length = portable_constant_pool_length;
  
  // Basic type length
  int32_t portable_basic_types_length = compiler->basic_types->length;
  portable->basic_types_length = portable_basic_types_length;
  
  // Package vars length
  int32_t portable_package_vars_length = compiler->package_vars->length;
  portable->package_vars_length = portable_package_vars_length;
  
  // Fields length
  int32_t portable_fields_length = compiler->fields->length;
  portable->fields_length = portable_fields_length;

  // Arg total length
  int32_t portable_args_length = 0;
  for (int32_t sub_index = 0; sub_index < compiler->subs->length; sub_index++) {
    SPVM_SUB* sub = SPVM_LIST_fetch(compiler->subs, sub_index);
    portable_args_length += sub->args->length;
  }
  portable->args_length = portable_args_length;
  
  // Subs length
  int32_t portable_subs_length = compiler->subs->length;
  portable->subs_length = portable_subs_length;
  
  // Packages length
  int32_t portable_packages_length = compiler->packages->length;
  portable->packages_length = portable_packages_length;
  
  // String pool length
  int32_t portable_string_pool_length = compiler->string_pool->length;
  portable->string_pool_length = portable_string_pool_length;
  
  // Total byte size(at least 1 byte)
  int32_t total_byte_size =
    sizeof(SPVM_OPCODE) * portable_opcode_length +
    sizeof(int32_t) * portable_constant_pool_length +
    sizeof(SPVM_RUNTIME_BASIC_TYPE) * portable_basic_types_length +
    sizeof(SPVM_RUNTIME_PACKAGE) * portable_package_vars_length +
    sizeof(SPVM_RUNTIME_FIELD) * portable_fields_length +
    sizeof(SPVM_RUNTIME_ARG) * portable_args_length +
    sizeof(SPVM_RUNTIME_SUB) * portable_subs_length +
    sizeof(SPVM_RUNTIME_PACKAGE) * portable_packages_length +
    portable_string_pool_length
    + 1
  ;
  
  char* memory_pool = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(total_byte_size);
  portable->memory_pool = memory_pool;
  
  int32_t memory_pool_base = 0;
  
  portable->opcodes = (SPVM_OPCODE*)&memory_pool[memory_pool_base];
  memory_pool_base += sizeof(int64_t) * portable_opcode_length;
  
  portable->constant_pool = (int32_t*)&memory_pool[memory_pool_base];
  memory_pool_base += sizeof(int32_t) * portable_constant_pool_length;
  
  portable->basic_types = (SPVM_RUNTIME_BASIC_TYPE*)&memory_pool[memory_pool_base];
  memory_pool_base += sizeof(SPVM_RUNTIME_BASIC_TYPE) * portable_basic_types_length;
  
  portable->package_vars = (SPVM_RUNTIME_PACKAGE_VAR*)&memory_pool[memory_pool_base];
  memory_pool_base += sizeof(SPVM_RUNTIME_PACKAGE_VAR) * portable_package_vars_length;

  portable->fields = (SPVM_RUNTIME_FIELD*)&memory_pool[memory_pool_base];
  memory_pool_base += sizeof(SPVM_RUNTIME_FIELD) * portable_fields_length;

  portable->args = (SPVM_RUNTIME_ARG*)&memory_pool[memory_pool_base];
  memory_pool_base += sizeof(SPVM_RUNTIME_ARG) * portable_args_length;

  portable->subs = (SPVM_RUNTIME_SUB*)&memory_pool[memory_pool_base];
  memory_pool_base += sizeof(SPVM_RUNTIME_SUB) * portable_subs_length;

  portable->packages = (SPVM_RUNTIME_PACKAGE*)&memory_pool[memory_pool_base];
  memory_pool_base += sizeof(SPVM_RUNTIME_PACKAGE) * portable_packages_length;

  portable->string_pool = &memory_pool[memory_pool_base];
  memory_pool_base += portable_string_pool_length;
  
  // OPCode(64bit)
  memcpy(portable->opcodes, compiler->opcode_array->values, sizeof(int64_t) * portable_opcode_length);
  
  // Global constant pool(32bit)
  int32_t constant_pool_index = 0;
  for (int32_t package_index = 0; package_index < compiler->packages->length; package_index++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
    package->constant_pool_base = constant_pool_index;
    memcpy(&portable->constant_pool[constant_pool_index], package->constant_pool->values, sizeof(int32_t) * package->constant_pool->length);
    constant_pool_index += package->constant_pool->length;
  }

  // Portable basic type(32bit)
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = &portable->basic_types[basic_type_id];
    runtime_basic_type->name_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, basic_type->name, strlen(basic_type->name) + 1);
    runtime_basic_type->id = basic_type->id;
    if (basic_type->package) {
      runtime_basic_type->package_id = basic_type->package->id;
    }
  }
  
  // Portable package_vars(32bit)
  for (int32_t package_var_id = 0; package_var_id < compiler->package_vars->length; package_var_id++) {
    SPVM_PACKAGE_VAR* package_var = SPVM_LIST_fetch(compiler->package_vars, package_var_id);
    
    SPVM_RUNTIME_PACKAGE_VAR* portable_package_var = &portable->package_vars[package_var_id];

    portable_package_var->id = package_var->id;
    portable_package_var->name_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, package_var->name, strlen(package_var->name) + 1);
    
    portable_package_var->signature_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, package_var->signature, strlen(package_var->signature) + 1);
    if (package_var->type->basic_type) {
      portable_package_var->basic_type_id = package_var->type->basic_type->id;
    }
    else {
      portable_package_var->basic_type_id = -1;
    }
    portable_package_var->type_dimension = package_var->type->dimension;
    portable_package_var->type_flag = package_var->type->flag;
    assert(package_var->package);
    portable_package_var->package_id = package_var->package->id;
  }

  // Portable fields(32bit)
  for (int32_t field_id = 0; field_id < compiler->fields->length; field_id++) {
    SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);
    SPVM_RUNTIME_FIELD* portable_field = &portable->fields[field_id];

    portable_field->id = field->id;
    portable_field->index = field->index;
    portable_field->byte_offset = field->byte_offset;
    portable_field->flag = field->flag;
    portable_field->name_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, field->name, strlen(field->name) + 1);
    portable_field->signature_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, field->signature, strlen(field->signature) + 1);
    if (field->type->basic_type) {
      portable_field->basic_type_id = field->type->basic_type->id;
    }
    else {
      portable_field->basic_type_id = -1;
    }
    portable_field->type_dimension = field->type->dimension;
    if (field->package) {
      portable_field->package_id = field->package->id;
    }
    portable_field->runtime_type = field->runtime_type;
  }
  
  // Portable args(32bit)

  // Portable subs(32bit)
  int32_t args_base = 0;
  for (int32_t sub_id = 0; sub_id < compiler->subs->length; sub_id++) {
    SPVM_SUB* sub = SPVM_LIST_fetch(compiler->subs, sub_id);

    SPVM_RUNTIME_SUB* portable_sub = &portable->subs[sub_id];

    portable_sub->id = sub->id;
    portable_sub->flag = sub->flag;
    portable_sub->name_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, sub->name, strlen(sub->name) + 1);
    portable_sub->signature_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, sub->signature, strlen(sub->signature) + 1);;
    if (sub->package) {
      portable_sub->package_id = sub->package->id;
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

    portable_sub->file_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, sub_file_base, strlen(sub_file_base) + 1);
    assert(portable_sub->file_id);
    portable_sub->line = sub->line;
    portable_sub->args_alloc_length = sub->args_alloc_length;
    portable_sub->return_basic_type_id = sub->return_type->basic_type->id;
    portable_sub->return_type_dimension = sub->return_type->dimension;
    portable_sub->return_type_flag = sub->return_type->flag;
    portable_sub->opcodes_base = sub->opcodes_base;
    portable_sub->mortal_stack_length = sub->mortal_stack_length;
    portable_sub->arg_ids_base = args_base;
    portable_sub->arg_ids_length = sub->args->length;
    portable_sub->opcodes_length = sub->opcodes_length;
    portable_sub->call_type_id = sub->call_type_id;
    portable_sub->byte_vars_alloc_length = sub->byte_vars_alloc_length;
    portable_sub->short_vars_alloc_length = sub->short_vars_alloc_length;
    portable_sub->int_vars_alloc_length = sub->int_vars_alloc_length;
    portable_sub->long_vars_alloc_length = sub->long_vars_alloc_length;
    portable_sub->float_vars_alloc_length = sub->float_vars_alloc_length;
    portable_sub->double_vars_alloc_length = sub->double_vars_alloc_length;
    portable_sub->object_vars_alloc_length = sub->object_vars_alloc_length;
    portable_sub->ref_vars_alloc_length = sub->ref_vars_alloc_length;
    portable_sub->return_runtime_type = sub->return_runtime_type;
    
    for (int32_t arg_id = 0; arg_id < sub->args->length; arg_id++) {
      SPVM_MY* arg = SPVM_LIST_fetch(sub->args, arg_id);
      
      SPVM_RUNTIME_ARG* portable_arg = &portable->args[args_base + arg_id];
      portable_arg->basic_type_id = arg->type->basic_type->id;
      portable_arg->type_dimension = arg->type->dimension;
      portable_arg->type_flag = arg->type->flag;
      portable_arg->var_id = arg->var_id;
      portable_arg->runtime_type = arg->runtime_type;
      portable_arg->type_width = arg->type_width;
    }
    args_base += sub->args->length;
  }
  
  // Portable packages(32bit)
  for (int32_t package_id = 0; package_id < compiler->packages->length; package_id++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_id);

    SPVM_RUNTIME_PACKAGE* portable_package = &portable->packages[package_id];
    
    portable_package->id = package->id;
    portable_package->name_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, package->name, strlen(package->name) + 1);
    if (package->sub_destructor) {
      portable_package->destructor_sub_id = package->sub_destructor->id;
    }
    else {
      portable_package->destructor_sub_id = -1;
    }
    portable_package->category = package->category;
    portable_package->flag = package->flag;

    portable_package->constant_pool_base = package->constant_pool_base;
    portable_package->no_dup_field_access_field_ids_constant_pool_id = package->no_dup_field_access_field_ids_constant_pool_id;
    portable_package->no_dup_package_var_access_package_var_ids_constant_pool_id = package->no_dup_package_var_access_package_var_ids_constant_pool_id;
    portable_package->no_dup_call_sub_sub_ids_constant_pool_id = package->no_dup_call_sub_sub_ids_constant_pool_id;
    portable_package->no_dup_basic_type_ids_constant_pool_id = package->no_dup_basic_type_ids_constant_pool_id;
    
    portable_package->fields_byte_size = package->fields_byte_size;
    portable_package->object_fields_byte_offset = package->object_fields_byte_offset;
    portable_package->object_fields_length = package->object_fields_length;

    if (package->fields->length > 0) {
      SPVM_FIELD* first_field = SPVM_LIST_fetch(package->fields, 0);
      portable_package->fields_base = first_field->id;
    }
    else {
      portable_package->fields_base = -1;
    }
    portable_package->fields_length = package->fields->length;
    
    if (package->subs->length > 0) {
      SPVM_SUB* first_sub = SPVM_LIST_fetch(package->subs, 0);
      portable_package->subs_base = first_sub->id;
    }
    else {
      portable_package->subs_base = -1;
    }
    portable_package->subs_length = package->subs->length;

    if (package->op_begin_sub) {
      portable_package->begin_sub_id = package->op_begin_sub->uv.sub->id;
    }
    else {
      portable_package->begin_sub_id = -1;
    }

    if (package->package_vars->length > 0) {
      SPVM_PACKAGE_VAR* first_package_var = SPVM_LIST_fetch(package->package_vars, 0);
      portable_package->package_vars_base = first_package_var->id;
    }
    else {
      portable_package->package_vars_base = -1;
    }
    portable_package->package_vars_length = package->package_vars->length;
    
  }

  // String pool(8bit)
  memcpy(portable->string_pool, compiler->string_pool->buffer, portable_string_pool_length);
  
  return portable;
}

void SPVM_PORTABLE_free(SPVM_PORTABLE* portable) {
  
  if (!portable->is_static) {
    free(portable->memory_pool);
    free(portable);
  }
}
