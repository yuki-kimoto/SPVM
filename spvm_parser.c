#include <stdlib.h>
#include <string.h>

#include "spvm_.h"
#include "spvm_parser.h"
#include "spvm_resolved_type.h"
#include "spvm_package.h"
#include "spvm_type_component_name.h"
#include "spvm_type.h"
#include "spvm_op.h"
#include "spvm_memory_pool.h"
#include "spvm_hash.h"
#include "spvm_array.h"
#include "spvm_util_allocator.h"
#include "spvm_parser_allocator.h"
#include "spvm_yacc_util.h"
#include "spvm_array.h"
#include "spvm_bytecode_array.h"
#include "spvm_sub.h"
#include "spvm_constant_pool.h"

SPVM_PARSER* SPVM_PARSER_new(SPVM_* spvm) {
  SPVM_PARSER* parser = malloc(sizeof(SPVM_PARSER));

  // Allocator
  parser->allocator = SPVM_PARSER_ALLOCATOR_new(spvm);
  
  spvm->parser = parser;
  
  // Parser information
  parser->op_sub_symtable = SPVM_PARSER_ALLOCATOR_alloc_hash(spvm, parser->allocator, 0);
  parser->op_packages = SPVM_PARSER_ALLOCATOR_alloc_array(spvm, parser->allocator, 0);
  parser->op_package_symtable = SPVM_PARSER_ALLOCATOR_alloc_hash(spvm, parser->allocator, 0);
  parser->op_types = SPVM_PARSER_ALLOCATOR_alloc_array(spvm, parser->allocator, 0);
  parser->op_use_symtable = SPVM_PARSER_ALLOCATOR_alloc_hash(spvm, parser->allocator, 0);
  parser->op_use_stack = SPVM_PARSER_ALLOCATOR_alloc_array(spvm, parser->allocator, 0);
  parser->op_field_symtable = SPVM_PARSER_ALLOCATOR_alloc_hash(spvm, parser->allocator, 0);
  parser->include_pathes = SPVM_PARSER_ALLOCATOR_alloc_array(spvm, parser->allocator, 0);
  parser->bufptr = "";
  parser->resolved_types = SPVM_PARSER_ALLOCATOR_alloc_array(spvm, parser->allocator, 0);
  parser->resolved_type_symtable = SPVM_PARSER_ALLOCATOR_alloc_hash(spvm, parser->allocator, 0);
  parser->cur_op_cases = SPVM_PARSER_ALLOCATOR_alloc_array(spvm, parser->allocator, 0);
  parser->cur_line = 0;

  // Constant pool
  parser->constant_pool = SPVM_CONSTANT_POOL_new(spvm);
  
  // Bytecodes
  parser->bytecode_array = SPVM_BYTECODE_ARRAY_new(spvm);

  // Entry point sub name
  parser->entry_point_sub_name = NULL;

  // Add core types
  for (int32_t i = 0; i < SPVM_RESOLVED_TYPE_C_CORE_LENGTH; i++) {
    // Resolved type
    SPVM_RESOLVED_TYPE* resolved_type = SPVM_RESOLVED_TYPE_new(spvm);
    const char* name = SPVM_RESOLVED_TYPE_C_CORE_NAMES[i];
    SPVM_ARRAY_push(spvm, resolved_type->part_names, (char*)name);
    resolved_type->name = name;
    resolved_type->name_length = strlen(name);
    resolved_type->id = i;
    SPVM_ARRAY_push(spvm, parser->resolved_types, resolved_type);
    SPVM_HASH_insert(spvm, parser->resolved_type_symtable, name, strlen(name), resolved_type);
  }
  
  return parser;
}

int32_t SPVM_PARSER_parse(SPVM_* spvm, const char* package_name) {
  
  SPVM_PARSER* parser = spvm->parser;

  /* Build use information */
  SPVM_OP* op_name_package = SPVM_OP_new_op(spvm, SPVM_OP_C_CODE_NAME, package_name, 1);
  op_name_package->uv.name = package_name;
  
  // Use OP
  SPVM_OP* op_use = SPVM_OP_new_op(spvm, SPVM_OP_C_CODE_USE, package_name, 1);
  SPVM_OP_sibling_splice(spvm, op_use, NULL, 0, op_name_package);
  
  /* Push package use information stack */
  SPVM_ARRAY_push(spvm, parser->op_use_stack, op_use);
  
  // Entry point
  int32_t package_name_length = (int32_t)strlen(package_name);
  int32_t entry_point_sub_name_length =  (int32_t)(package_name_length + 6);
  char* entry_point_sub_name = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(entry_point_sub_name_length + 1, sizeof(char));
  strncpy(entry_point_sub_name, package_name, package_name_length);
  strncpy(entry_point_sub_name + package_name_length, "::main", 6);
  entry_point_sub_name[entry_point_sub_name_length] = '\0';
  parser->entry_point_sub_name = entry_point_sub_name;

  // use standard module
  SPVM_OP* op_use_std = SPVM_OP_new_op(spvm, SPVM_OP_C_CODE_USE, "std", 0);
  SPVM_OP* op_std_package_name = SPVM_OP_new_op(spvm, SPVM_OP_C_CODE_NAME, "std", 0);
  op_std_package_name->uv.name = "std";
  SPVM_OP_sibling_splice(spvm, op_use_std, NULL, 0, op_std_package_name);
  SPVM_ARRAY_push(spvm, parser->op_use_stack, op_use_std);
  SPVM_HASH_insert(spvm, parser->op_use_symtable, op_std_package_name->uv.name, strlen(op_std_package_name->uv.name), op_use_std);
  
  /* call SPVM_yyparse */
  SPVM_yydebug = 0;
  int32_t parse_success = SPVM_yyparse(spvm);
  
  return parse_success;
}

void SPVM_PARSER_free(SPVM_* spvm, SPVM_PARSER* parser) {
  
  // Free allocator
  SPVM_PARSER_ALLOCATOR_free(spvm, parser->allocator);

  // Free constant pool
  SPVM_CONSTANT_POOL_free(spvm, parser->constant_pool);
  
  // Free bytecode array
  SPVM_BYTECODE_ARRAY_free(spvm, parser->bytecode_array);
  
  free(parser);
}
