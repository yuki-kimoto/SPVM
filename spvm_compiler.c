#include <stdlib.h>
#include <string.h>

#include "spvm_compiler.h"
#include "spvm_type.h"
#include "spvm_package.h"
#include "spvm_type.h"
#include "spvm_op.h"
#include "spvm_memory_pool.h"
#include "spvm_hash.h"
#include "spvm_dynamic_array.h"
#include "spvm_util_allocator.h"
#include "spvm_compiler_allocator.h"
#include "spvm_yacc_util.h"
#include "spvm_dynamic_array.h"
#include "spvm_bytecode_array.h"
#include "spvm_sub.h"
#include "spvm_constant_pool.h"
#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_global.h"
#include "spvm_sub.h"
#include "spvm_field_info.h"

SPVM_RUNTIME* SPVM_COMPILER_new_runtime(SPVM_COMPILER* compiler) {
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_new();
  
  // Set global runtime
  SPVM_RUNTIME_API_set_runtime(runtime->api, runtime);
  
  // Copy constant pool to runtime
  int64_t runtime_constant_pool_byte_size = (int64_t)compiler->constant_pool->length * (int64_t)sizeof(int32_t);
  runtime->constant_pool = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(runtime_constant_pool_byte_size);
  memcpy(runtime->constant_pool, compiler->constant_pool->values, compiler->constant_pool->length * sizeof(int32_t));
  
  // Copy bytecodes to runtime
  int64_t runtime_bytecodes_byte_size = (int64_t)compiler->bytecode_array->length * (int64_t)sizeof(uint8_t);
  runtime->bytecodes = SPVM_UTIL_ALLOCATOR_safe_malloc(runtime_bytecodes_byte_size);
  memcpy(runtime->bytecodes, compiler->bytecode_array->values, compiler->bytecode_array->length * sizeof(uint8_t));
  
  // Build constant pool sub symtable
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < compiler->op_subs->length; sub_index++) {
      SPVM_OP* op_sub = SPVM_DYNAMIC_ARRAY_fetch(compiler->op_subs, sub_index);
      SPVM_SUB* sub = op_sub->uv.sub;
      SPVM_HASH_insert(runtime->sub_id_symtable, sub->abs_name, strlen(sub->abs_name), (void*)(intptr_t)sub->id);
    }
  }
  
  // Build constant pool type symtable
  {
    int32_t type_index;
    for (type_index = 0; type_index < compiler->types->length; type_index++) {
      SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, type_index);
      SPVM_HASH_insert(runtime->type_id_symtable, type->name, strlen(type->name), (void*)(intptr_t)type->id);
    }
  }
  
  // Build constant pool field symtable
  {
    int32_t package_index;
    for (package_index = 0; package_index < compiler->op_packages->length; package_index++) {
      SPVM_OP* op_package = SPVM_DYNAMIC_ARRAY_fetch(compiler->op_packages, package_index);
      SPVM_PACKAGE* package = op_package->uv.package;
      const char* package_name = package->op_name->uv.name;
      
      SPVM_DYNAMIC_ARRAY* op_fields = package->op_fields;
      SPVM_HASH* field_name_symtable = SPVM_HASH_new(0);
      {
        int32_t op_field_index;
        for (op_field_index = 0; op_field_index < op_fields->length; op_field_index++) {
          SPVM_OP* op_field = SPVM_DYNAMIC_ARRAY_fetch(op_fields, op_field_index);
          SPVM_FIELD_INFO* field_info = op_field->uv.field;
          const char* field_name = field_info->op_name->uv.name;
          
          SPVM_HASH_insert(field_name_symtable, field_name, strlen(field_name), (void*)(intptr_t)(field_info->index + 1));
        }
      }
      
      SPVM_HASH_insert(runtime->field_id_symtable, package_name, strlen(package_name), field_name_symtable);
    }
  }
  
  SPVM_DYNAMIC_ARRAY* op_packages = compiler->op_packages;
  
  runtime->packages_length = op_packages->length;
  
  runtime->packages_base = compiler->packages_base;
  
  runtime->subs_base = compiler->subs_base;
  
  runtime->subs_length = compiler->op_subs->length;

  runtime->types_base = compiler->types_base;
  
  runtime->type_code_to_id_base = compiler->type_code_to_id_base;
  
  runtime->types_length = compiler->types->length;
  
  runtime->debug = compiler->debug;
  
  return runtime;
}

SPVM_COMPILER* SPVM_COMPILER_new() {
  SPVM_COMPILER* compiler = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_COMPILER));

  // Allocator
  compiler->allocator = SPVM_COMPILER_ALLOCATOR_new(compiler);
  
  // Parser information
  compiler->op_sub_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, compiler->allocator, 0);
  compiler->op_packages = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  compiler->op_package_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, compiler->allocator, 0);
  compiler->op_types = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  compiler->op_use_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, compiler->allocator, 0);
  compiler->op_use_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  compiler->op_field_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, compiler->allocator, 0);
  compiler->op_fields = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  compiler->include_pathes = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  compiler->bufptr = "";
  compiler->types = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  compiler->type_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, compiler->allocator, 0);
  compiler->op_constants = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  compiler->op_subs = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  
  compiler->native_subs = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);

  compiler->enum_default_type_code = SPVM_TYPE_C_CODE_INT;

  // Constant pool
  compiler->constant_pool = SPVM_CONSTANT_POOL_new(compiler);
  
  // Bytecodes
  compiler->bytecode_array = SPVM_BYTECODE_ARRAY_new(compiler);
  
  // Add core types
  {
    int32_t type_code;
    for (type_code = 0; type_code < SPVM_TYPE_C_CORE_LENGTH; type_code++) {
      // Type
      SPVM_TYPE* type = SPVM_TYPE_new(compiler);
      const char* name = SPVM_TYPE_C_CODE_NAMES[type_code];
      type->name = name;
      type->code = type_code;
      if (type_code >= SPVM_TYPE_C_CODE_BYTE_ARRAY && type_code <= SPVM_TYPE_C_CODE_STRING_ARRAY) {
        type->dimension++;
        type->base_type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, type_code - SPVM_TYPE_C_ARRAY_SHIFT);
      }
      else {
        type->base_type = type;
      }
      SPVM_DYNAMIC_ARRAY_push(compiler->types, type);
      SPVM_HASH_insert(compiler->type_symtable, name, strlen(name), type);
    }
  }
  
  return compiler;
}

int32_t SPVM_COMPILER_compile(SPVM_COMPILER* compiler) {
  
  const char* entyr_point_package_name = compiler->entry_point_package_name;
  
  if (entyr_point_package_name) {
    // Create use op for entry point package
    SPVM_OP* op_use_entry_point = SPVM_OP_new_op_use_from_package_name(compiler, entyr_point_package_name, "main", 1);
    SPVM_DYNAMIC_ARRAY_push(compiler->op_use_stack, op_use_entry_point);
    SPVM_HASH_insert(compiler->op_use_symtable, entyr_point_package_name, strlen(entyr_point_package_name), op_use_entry_point);
    
    // Entry point
    int32_t entyr_point_package_name_length = (int32_t)strlen(entyr_point_package_name);
    int32_t entry_point_sub_name_length =  (int32_t)(entyr_point_package_name_length + 6);
    char* entry_point_sub_name = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(entry_point_sub_name_length + 1);
    strncpy(entry_point_sub_name, entyr_point_package_name, entyr_point_package_name_length);
    strncpy(entry_point_sub_name + entyr_point_package_name_length, "::main", 6);
    entry_point_sub_name[entry_point_sub_name_length] = '\0';
    compiler->entry_point_sub_name = entry_point_sub_name;
  }
  
  // use standard module
  SPVM_OP* op_use_std = SPVM_OP_new_op_use_from_package_name(compiler, "std", "CORE", 0);
  SPVM_DYNAMIC_ARRAY_push(compiler->op_use_stack, op_use_std);
  SPVM_HASH_insert(compiler->op_use_symtable, "std", strlen("std"), op_use_std);
  
  /* call SPVM_yyparse */
  SPVM_yydebug = 0;
  int32_t parse_success = SPVM_yyparse(compiler);
  
  return parse_success;
}

void SPVM_COMPILER_free(SPVM_COMPILER* compiler) {
  
  // Free allocator
  SPVM_COMPILER_ALLOCATOR_free(compiler, compiler->allocator);

  // Free constant pool
  SPVM_CONSTANT_POOL_free(compiler, compiler->constant_pool);
  
  // Free bytecode array
  SPVM_BYTECODE_ARRAY_free(compiler, compiler->bytecode_array);
  
  free(compiler);
}
