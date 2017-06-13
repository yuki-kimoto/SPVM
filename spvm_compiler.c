#include <stdlib.h>
#include <string.h>


#include "spvm_compiler.h"
#include "spvm_resolved_type.h"
#include "spvm_package.h"
#include "spvm_type_component_name.h"
#include "spvm_type.h"
#include "spvm_op.h"
#include "spvm_memory_pool.h"
#include "spvm_hash.h"
#include "spvm_array.h"
#include "spvm_util_allocator.h"
#include "spvm_compiler_allocator.h"
#include "spvm_yacc_util.h"
#include "spvm_array.h"
#include "spvm_bytecode_array.h"
#include "spvm_sub.h"
#include "spvm_constant_pool.h"

SPVM_COMPILER* SPVM_COMPILER_new() {
  SPVM_COMPILER* compiler = malloc(sizeof(SPVM_COMPILER));

  // Allocator
  compiler->allocator = SPVM_COMPILER_ALLOCATOR_new(compiler);
  
  compiler = compiler;
  
  // Parser information
  compiler->op_sub_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, compiler->allocator, 0);
  compiler->op_packages = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  compiler->op_package_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, compiler->allocator, 0);
  compiler->op_types = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  compiler->op_use_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, compiler->allocator, 0);
  compiler->op_use_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  compiler->op_field_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, compiler->allocator, 0);
  compiler->include_pathes = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  compiler->bufptr = "";
  compiler->resolved_types = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  compiler->resolved_type_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, compiler->allocator, 0);
  compiler->cur_op_cases = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  compiler->cur_line = 0;
  
  // Error count
  compiler->error_count = 0;

  // Constant pool
  compiler->constant_pool = SPVM_CONSTANT_POOL_new(compiler);
  
  // Bytecodes
  compiler->bytecode_array = SPVM_BYTECODE_ARRAY_new(compiler);

  // Entry point package name
  compiler->entry_point_package_name = NULL;

  // Entry point sub name
  compiler->entry_point_sub_name = NULL;

  // Add core types
  for (int32_t i = 0; i < SPVM_RESOLVED_TYPE_C_CORE_LENGTH; i++) {
    // Resolved type
    SPVM_RESOLVED_TYPE* resolved_type = SPVM_RESOLVED_TYPE_new(compiler);
    const char* name = SPVM_RESOLVED_TYPE_C_CORE_NAMES[i];
    SPVM_ARRAY_push(resolved_type->part_names, (char*)name);
    resolved_type->name = name;
    resolved_type->name_length = strlen(name);
    resolved_type->id = i;
    SPVM_ARRAY_push(compiler->resolved_types, resolved_type);
    SPVM_HASH_insert(compiler->resolved_type_symtable, name, strlen(name), resolved_type);
  }
  
  return compiler;
}

int32_t SPVM_COMPILER_compile(SPVM_COMPILER* compiler) {
  
  const char* entyr_point_package_name = compiler->entry_point_package_name;
  
  if (entyr_point_package_name) {
    // Create use op for entry point package
    SPVM_OP* op_use_entry_point = SPVM_OP_new_op_use_from_package_name(compiler, entyr_point_package_name, "main", 1);
    SPVM_ARRAY_push(compiler->op_use_stack, op_use_entry_point);
    SPVM_HASH_insert(compiler->op_use_symtable, entyr_point_package_name, strlen(entyr_point_package_name), op_use_entry_point);
    
    // Entry point
    int32_t entyr_point_package_name_length = (int32_t)strlen(entyr_point_package_name);
    int32_t entry_point_sub_name_length =  (int32_t)(entyr_point_package_name_length + 6);
    char* entry_point_sub_name = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(entry_point_sub_name_length + 1, sizeof(char));
    strncpy(entry_point_sub_name, entyr_point_package_name, entyr_point_package_name_length);
    strncpy(entry_point_sub_name + entyr_point_package_name_length, "::main", 6);
    entry_point_sub_name[entry_point_sub_name_length] = '\0';
    compiler->entry_point_sub_name = entry_point_sub_name;
  }
  
  // use standard module
  SPVM_OP* op_use_std = SPVM_OP_new_op_use_from_package_name(compiler, "std", "CORE", 0);
  SPVM_ARRAY_push(compiler->op_use_stack, op_use_std);
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
