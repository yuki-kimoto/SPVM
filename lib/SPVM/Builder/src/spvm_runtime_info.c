#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_runtime_info.h"

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

SPVM_RUNTIME_INFO* SPVM_RUNTIME_INFO_new() {
  
  SPVM_RUNTIME_INFO* runtime_info = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_INFO));

  return runtime_info;
}

SPVM_RUNTIME_INFO* SPVM_RUNTIME_INFO_build_runtime_info(SPVM_COMPILER* compiler) {
  SPVM_RUNTIME_INFO* runtime_info = SPVM_RUNTIME_INFO_new();

  // Opcode Length
  int32_t runtime_info_opcode_length = compiler->opcode_array->length;
  runtime_info->opcodes_length = runtime_info_opcode_length;
  
  // Constant pool length
  int32_t runtime_info_constant_pool_length = 0;
  for (int32_t package_index = 0; package_index < compiler->packages->length; package_index++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
    runtime_info_constant_pool_length += package->constant_pool->length;
  }
  runtime_info->constant_pool_length = runtime_info_constant_pool_length;
  
  // Basic type length
  int32_t runtime_info_basic_types_length = compiler->basic_types->length;
  runtime_info->basic_types_length = runtime_info_basic_types_length;
  
  // Package vars length
  int32_t runtime_info_package_vars_length = compiler->package_vars->length;
  runtime_info->package_vars_length = runtime_info_package_vars_length;
  
  // Fields length
  int32_t runtime_info_fields_length = compiler->fields->length;
  runtime_info->fields_length = runtime_info_fields_length;

  // Arg total length
  int32_t runtime_info_args_length = 0;
  for (int32_t sub_index = 0; sub_index < compiler->subs->length; sub_index++) {
    SPVM_SUB* sub = SPVM_LIST_fetch(compiler->subs, sub_index);
    runtime_info_args_length += sub->args->length;
  }
  runtime_info->args_length = runtime_info_args_length;
  
  // Subs length
  int32_t runtime_info_subs_length = compiler->subs->length;
  runtime_info->subs_length = runtime_info_subs_length;
  
  // Packages length
  int32_t runtime_info_packages_length = compiler->packages->length;
  runtime_info->packages_length = runtime_info_packages_length;
  
  // String pool length
  int32_t runtime_info_string_pool_length = compiler->string_pool->length;
  runtime_info->string_pool_length = runtime_info_string_pool_length;
  
  // Total byte size(at least 1 byte)
  int32_t total_byte_size =
    sizeof(SPVM_OPCODE) * runtime_info_opcode_length +
    sizeof(int32_t) * runtime_info_constant_pool_length +
    sizeof(SPVM_RUNTIME_BASIC_TYPE) * runtime_info_basic_types_length +
    sizeof(SPVM_RUNTIME_PACKAGE) * runtime_info_package_vars_length +
    sizeof(SPVM_RUNTIME_FIELD) * runtime_info_fields_length +
    sizeof(SPVM_RUNTIME_ARG) * runtime_info_args_length +
    sizeof(SPVM_RUNTIME_SUB) * runtime_info_subs_length +
    sizeof(SPVM_RUNTIME_PACKAGE) * runtime_info_packages_length +
    runtime_info_string_pool_length
    + 1
  ;
  
  char* memory_pool = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(total_byte_size);
  runtime_info->memory_pool = memory_pool;
  
  int32_t memory_pool_base = 0;
  
  runtime_info->opcodes = (SPVM_OPCODE*)&memory_pool[memory_pool_base];
  memory_pool_base += sizeof(SPVM_OPCODE) * runtime_info_opcode_length;
  
  runtime_info->constant_pool = (int32_t*)&memory_pool[memory_pool_base];
  memory_pool_base += sizeof(int32_t) * runtime_info_constant_pool_length;
  
  runtime_info->basic_types = (SPVM_RUNTIME_BASIC_TYPE*)&memory_pool[memory_pool_base];
  memory_pool_base += sizeof(SPVM_RUNTIME_BASIC_TYPE) * runtime_info_basic_types_length;
  
  runtime_info->package_vars = (SPVM_RUNTIME_PACKAGE_VAR*)&memory_pool[memory_pool_base];
  memory_pool_base += sizeof(SPVM_RUNTIME_PACKAGE_VAR) * runtime_info_package_vars_length;

  runtime_info->fields = (SPVM_RUNTIME_FIELD*)&memory_pool[memory_pool_base];
  memory_pool_base += sizeof(SPVM_RUNTIME_FIELD) * runtime_info_fields_length;

  runtime_info->args = (SPVM_RUNTIME_ARG*)&memory_pool[memory_pool_base];
  memory_pool_base += sizeof(SPVM_RUNTIME_ARG) * runtime_info_args_length;

  runtime_info->subs = (SPVM_RUNTIME_SUB*)&memory_pool[memory_pool_base];
  memory_pool_base += sizeof(SPVM_RUNTIME_SUB) * runtime_info_subs_length;

  runtime_info->packages = (SPVM_RUNTIME_PACKAGE*)&memory_pool[memory_pool_base];
  memory_pool_base += sizeof(SPVM_RUNTIME_PACKAGE) * runtime_info_packages_length;

  runtime_info->string_pool = &memory_pool[memory_pool_base];
  memory_pool_base += runtime_info_string_pool_length;
  
  // OPCode(64bit)
  memcpy(runtime_info->opcodes, compiler->opcode_array->values, sizeof(SPVM_OPCODE) * runtime_info_opcode_length);
  
  // Global constant pool(32bit)
  int32_t constant_pool_index = 0;
  for (int32_t package_index = 0; package_index < compiler->packages->length; package_index++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
    package->constant_pool_base = constant_pool_index;
    memcpy(&runtime_info->constant_pool[constant_pool_index], package->constant_pool->values, sizeof(int32_t) * package->constant_pool->length);
    constant_pool_index += package->constant_pool->length;
  }

  // Portable basic type(32bit)
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = &runtime_info->basic_types[basic_type_id];
    runtime_basic_type->name_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, basic_type->name, strlen(basic_type->name) + 1);
    runtime_basic_type->id = basic_type->id;
    if (basic_type->package) {
      runtime_basic_type->package_id = basic_type->package->id;
    }
  }
  
  // Portable package_vars(32bit)
  for (int32_t package_var_id = 0; package_var_id < compiler->package_vars->length; package_var_id++) {
    SPVM_PACKAGE_VAR* package_var = SPVM_LIST_fetch(compiler->package_vars, package_var_id);
    
    SPVM_RUNTIME_PACKAGE_VAR* runtime_info_package_var = &runtime_info->package_vars[package_var_id];

    runtime_info_package_var->id = package_var->id;
    runtime_info_package_var->name_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, package_var->name, strlen(package_var->name) + 1);
    
    runtime_info_package_var->signature_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, package_var->signature, strlen(package_var->signature) + 1);
    if (package_var->type->basic_type) {
      runtime_info_package_var->basic_type_id = package_var->type->basic_type->id;
    }
    else {
      runtime_info_package_var->basic_type_id = -1;
    }
    runtime_info_package_var->type_dimension = package_var->type->dimension;
    runtime_info_package_var->type_flag = package_var->type->flag;
    assert(package_var->package);
    runtime_info_package_var->package_id = package_var->package->id;
  }

  // Portable fields(32bit)
  for (int32_t field_id = 0; field_id < compiler->fields->length; field_id++) {
    SPVM_FIELD* field = SPVM_LIST_fetch(compiler->fields, field_id);
    SPVM_RUNTIME_FIELD* runtime_info_field = &runtime_info->fields[field_id];

    runtime_info_field->id = field->id;
    runtime_info_field->index = field->index;
    runtime_info_field->offset = field->offset;
    runtime_info_field->flag = field->flag;
    runtime_info_field->name_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, field->name, strlen(field->name) + 1);
    runtime_info_field->signature_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, field->signature, strlen(field->signature) + 1);
    if (field->type->basic_type) {
      runtime_info_field->basic_type_id = field->type->basic_type->id;
    }
    else {
      runtime_info_field->basic_type_id = -1;
    }
    runtime_info_field->type_dimension = field->type->dimension;
    if (field->package) {
      runtime_info_field->package_id = field->package->id;
    }
    runtime_info_field->runtime_type_category = field->runtime_type_category;
  }
  
  // Portable args(32bit)

  // Portable subs(32bit)
  int32_t args_base = 0;
  for (int32_t sub_id = 0; sub_id < compiler->subs->length; sub_id++) {
    SPVM_SUB* sub = SPVM_LIST_fetch(compiler->subs, sub_id);

    SPVM_RUNTIME_SUB* runtime_info_sub = &runtime_info->subs[sub_id];

    runtime_info_sub->id = sub->id;
    runtime_info_sub->flag = sub->flag;
    runtime_info_sub->name_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, sub->name, strlen(sub->name) + 1);
    runtime_info_sub->signature_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, sub->signature, strlen(sub->signature) + 1);;
    if (sub->package) {
      runtime_info_sub->package_id = sub->package->id;
    }
    
    runtime_info_sub->file_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, sub->package->module_rel_file, strlen(sub->package->module_rel_file) + 1);
    assert(runtime_info_sub->file_id);
    runtime_info_sub->line = sub->line;
    runtime_info_sub->args_alloc_length = sub->args_alloc_length;


    int32_t runtime_return_basic_type_id;
    int32_t runtime_return_type_dimension;
    if (sub->return_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_STRING) {
      runtime_return_basic_type_id = SPVM_BASIC_TYPE_C_ID_BYTE;
      runtime_return_type_dimension = sub->return_type->dimension + 1;
    }
    else {
      runtime_return_basic_type_id = sub->return_type->basic_type->id;
      runtime_return_type_dimension = sub->return_type->dimension;
    }

    runtime_info_sub->return_basic_type_id = runtime_return_basic_type_id;
    runtime_info_sub->return_type_dimension = runtime_return_type_dimension;
    runtime_info_sub->return_type_flag = sub->return_type->flag;
    runtime_info_sub->opcodes_base = sub->opcodes_base;
    runtime_info_sub->mortal_stack_length = sub->mortal_stack_length;
    runtime_info_sub->arg_ids_base = args_base;
    runtime_info_sub->arg_ids_length = sub->args->length;
    runtime_info_sub->opcodes_length = sub->opcodes_length;
    runtime_info_sub->call_type_id = sub->call_type_id;
    runtime_info_sub->byte_vars_alloc_length = sub->byte_vars_alloc_length;
    runtime_info_sub->short_vars_alloc_length = sub->short_vars_alloc_length;
    runtime_info_sub->int_vars_alloc_length = sub->int_vars_alloc_length;
    runtime_info_sub->long_vars_alloc_length = sub->long_vars_alloc_length;
    runtime_info_sub->float_vars_alloc_length = sub->float_vars_alloc_length;
    runtime_info_sub->double_vars_alloc_length = sub->double_vars_alloc_length;
    runtime_info_sub->object_vars_alloc_length = sub->object_vars_alloc_length;
    runtime_info_sub->ref_vars_alloc_length = sub->ref_vars_alloc_length;
    runtime_info_sub->return_runtime_type_category = sub->return_runtime_type_category;
    
    for (int32_t arg_id = 0; arg_id < sub->args->length; arg_id++) {
      SPVM_MY* arg = SPVM_LIST_fetch(sub->args, arg_id);
      
      SPVM_RUNTIME_ARG* runtime_info_arg = &runtime_info->args[args_base + arg_id];

      int32_t runtime_basic_type_id;
      int32_t runtime_type_category_dimension;
      if (arg->type->basic_type->id == SPVM_BASIC_TYPE_C_ID_STRING) {
        runtime_basic_type_id = SPVM_BASIC_TYPE_C_ID_BYTE;
        runtime_type_category_dimension = arg->type->dimension + 1;
      }
      else {
        runtime_basic_type_id = arg->type->basic_type->id;
        runtime_type_category_dimension = arg->type->dimension;
      }

      runtime_info_arg->basic_type_id = runtime_basic_type_id;
      runtime_info_arg->type_dimension = runtime_type_category_dimension;
      runtime_info_arg->type_flag = arg->type->flag;
      runtime_info_arg->mem_id = arg->mem_id;
      runtime_info_arg->runtime_type_category = arg->runtime_type_category;
      runtime_info_arg->type_width = arg->type_width;
    }
    args_base += sub->args->length;
  }
  
  // Portable packages(32bit)
  for (int32_t package_id = 0; package_id < compiler->packages->length; package_id++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_id);

    SPVM_RUNTIME_PACKAGE* runtime_info_package = &runtime_info->packages[package_id];
    
    runtime_info_package->id = package->id;
    runtime_info_package->name_id = (intptr_t)SPVM_HASH_fetch(compiler->string_symtable, package->name, strlen(package->name) + 1);
    if (package->sub_destructor) {
      runtime_info_package->destructor_sub_id = package->sub_destructor->id;
    }
    else {
      runtime_info_package->destructor_sub_id = -1;
    }
    runtime_info_package->category = package->category;
    runtime_info_package->flag = package->flag;

    runtime_info_package->constant_pool_base = package->constant_pool_base;
    runtime_info_package->no_dup_field_access_field_ids_constant_pool_id = package->no_dup_field_access_field_ids_constant_pool_id;
    runtime_info_package->no_dup_package_var_access_package_var_ids_constant_pool_id = package->no_dup_package_var_access_package_var_ids_constant_pool_id;
    runtime_info_package->no_dup_call_sub_sub_ids_constant_pool_id = package->no_dup_call_sub_sub_ids_constant_pool_id;
    runtime_info_package->no_dup_basic_type_ids_constant_pool_id = package->no_dup_basic_type_ids_constant_pool_id;
    
    runtime_info_package->fields_byte_size = package->fields_byte_size;
    runtime_info_package->object_fields_offset = package->object_fields_offset;
    runtime_info_package->object_fields_length = package->object_fields_length;

    if (package->fields->length > 0) {
      SPVM_FIELD* first_field = SPVM_LIST_fetch(package->fields, 0);
      runtime_info_package->fields_base = first_field->id;
    }
    else {
      runtime_info_package->fields_base = -1;
    }
    runtime_info_package->fields_length = package->fields->length;
    
    if (package->subs->length > 0) {
      SPVM_SUB* first_sub = SPVM_LIST_fetch(package->subs, 0);
      runtime_info_package->subs_base = first_sub->id;
    }
    else {
      runtime_info_package->subs_base = -1;
    }
    runtime_info_package->subs_length = package->subs->length;

    if (package->op_begin_sub) {
      runtime_info_package->begin_sub_id = package->op_begin_sub->uv.sub->id;
    }
    else {
      runtime_info_package->begin_sub_id = -1;
    }

    if (package->package_vars->length > 0) {
      SPVM_PACKAGE_VAR* first_package_var = SPVM_LIST_fetch(package->package_vars, 0);
      runtime_info_package->package_vars_base = first_package_var->id;
    }
    else {
      runtime_info_package->package_vars_base = -1;
    }
    runtime_info_package->package_vars_length = package->package_vars->length;
  }

  // String pool(8bit)
  memcpy(runtime_info->string_pool, compiler->string_pool->buffer, runtime_info_string_pool_length);
  
  return runtime_info;
}

void SPVM_RUNTIME_INFO_free(SPVM_RUNTIME_INFO* runtime_info) {
  
  if (!runtime_info->is_static) {
    free(runtime_info->memory_pool);
    free(runtime_info);
  }
}
